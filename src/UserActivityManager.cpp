#include <vector>
#include <Windows.h>
#include <sstream>
#include <fstream>

#include <nlohmann/json.hpp>
#include "discord-files/discord.h"

#include "UserActivityManager.h"
#include "iocontrol.h"
#include "ConfigManager.h"

using namespace io; // iocontro.h, namespace
using namespace std;
using namespace nlohmann; // JSON library namespace
using namespace discord; // Discord library namespace

bool SelectAct(UActivityManager::ConfigManager* CfgMgr, string question, json* Config); // List activities as options to user & asks for input.
void AddActivity(UActivityManager::ConfigManager* CfgMgr); // Gets info about what to add.
void ShowActivities(UActivityManager::ConfigManager* CfgMgr); // Lists Activities.
void Callback(Result); // Handles activity's launch callback.
void ConfigActivity(json*, Activity*); // Gets JSON, Returns Activity.
void RemoveActivity(UActivityManager::ConfigManager* CfgMgr); // Gets info about which to delete.
void RunActivity(UActivityManager::ConfigManager* CfgMgr); // Gets info about which to launch.

// This function executes from main file, when user selects.
void UActivityManager::run() {
	ClearEnv();
	
	// List & Print Options.
	vector<string> options = { "Add Activity", "Remove Activity",
		"Show Listed Activites" ,"Launch Activity"};
	PrintOptions(&options);

	// Get input from options.
	string choiceStr;
	GetInput("Select: ", &choiceStr);
	int choice = atoi(choiceStr.c_str());
	
	UActivityManager::ConfigManager CfgMgr;
	// Validate input & handle.
	switch (choice) {
	case 1:
		AddActivity(&CfgMgr);
		break;
	case 2:
		RemoveActivity(&CfgMgr);
		break;
	case 3:
		ShowActivities(&CfgMgr);
		break;
	case 4:
		RunActivity(&CfgMgr);
		break;
	default:
		PrintErr("Invalid Option!");
		cin.get();
		return;
	}
	return;
}

// Lists activities and asks user to select one with specified question
// Returns 1 if successfully got 
bool SelectAct(UActivityManager::ConfigManager* CfgMgr, string question = "", json* Config = new json) {
	
	// List Activities & Print them.
	vector<json> activities;
	CfgMgr->ListActivities(&activities); // Recieve Activities as vector.
	
	vector<string> messages;

	// Construct Options as vector.
	for (unsigned int i = 0; i < activities.size(); i++) {
		string tmp;
		ActivitytoStr(&activities[i], &tmp);
		messages.push_back(tmp);
	}
	
	PrintOptions(&messages);

	// Get input from options.
	string resultStr;
	if (question.size() > 1) {

		GetInput(question.c_str(), &resultStr);
		size_t result = atoi(resultStr.c_str()) - 1;
		
		if (result > activities.size() || result < 0) {
			PrintErr("Option Out of Range.");
			cin.get();
			return 0;
		}
		
		*Config = activities[result];
		return 1;
	}

	cin.get();
	return 1;
}

// This function executes from UActivityManager::run(), when user selects.
void RunActivity(UActivityManager::ConfigManager* CfgMgr) {
	ClearEnv();
	json Config;
	bool res = SelectAct(CfgMgr,"Select One to Launch: ", &Config);
	if (!res) return;

	Activity Act;
	ConfigActivity(&Config, &Act); // Configure activity from json.
	UActivityManager::LaunchActivity(&Act); // Launchs activity.
}

// Configures Activity from json ( json constructed by other functions, from input ).
void ConfigActivity(json* Config, Activity* act) {

	//Config State & Details.
	int64_t App_ID = (int64_t)(*Config)["Application_ID"];
	string state = (string)(*Config)["State"];
	string details = (string)(*Config)["Details"];

	act->SetApplicationId(App_ID);
	act->SetType(ActivityType::Playing);
	act->SetState(state.c_str());
	act->SetDetails(details.c_str());

	//Config TimeStamp.
	bool timestamp = (bool)(*Config)["HasTimeStamp"];
	if (timestamp) {
		time_t nowStamp;
		time(&nowStamp);

		ActivityTimestamps* stamps = &act->GetTimestamps();
		stamps->SetStart(nowStamp);
		stamps->SetEnd(0);
	}

	//Config Assets.
	string large_image = (string)(*Config)["LargeImage"];
	string large_text = (string)(*Config)["LargeText"];
	string small_image = (string)(*Config)["SmallImage"];
	string small_text = (string)(*Config)["SmallText"];
	ActivityAssets* assets = &act->GetAssets();
	assets->SetLargeImage(large_image.c_str());
	assets->SetLargeText(large_text.c_str());
	assets->SetSmallImage(small_image.c_str());
	assets->SetSmallText(small_text.c_str());

	//Empty Party.
	ActivityParty* party = &act->GetParty();
	party->SetId("");
	PartySize* size = &party->GetSize();
	size->SetCurrentSize(0);
	size->SetMaxSize(0);

	//Empty Secrets.
	ActivitySecrets* secrets = &act->GetSecrets();
	secrets->SetJoin("");
	secrets->SetMatch("");
	secrets->SetSpectate("");

	//Config Instance.
	act->SetInstance(true);
}

// This function executes from UActivityManager::run(), when user selects.
void RemoveActivity(UActivityManager::ConfigManager* CfgMgr) {
	ClearEnv();
	json Config;
	bool res = SelectAct(CfgMgr, "Select One to Remove: ", &Config);
	if (!res) return;

	CfgMgr->RemoveActivity(&Config); // Remove activity from config.
	ostringstream ss;
	ss << "Successfully Deleted ";
	ss << Config["Application_ID"] << ".";
	PrintSuc(ss.str().c_str());
	cin.get();
}

// This function executes from UActivityManager::run(), when user selects.
void ShowActivities(UActivityManager::ConfigManager* CfgMgr) {
	ClearEnv();
	SelectAct(CfgMgr);
}

// This function executes from UActivityManager::run(), when user selects.
void AddActivity(UActivityManager::ConfigManager* CfgMgr) {
	ClearEnv();

	json Act;

	// Initialize app ID with user input.
	uint64_t app_id;
	while (true) {
		// Validate user input.
		try {
			string app_idStr;
			GetInput("Enter Activity Application ID: ", &app_idStr);
			app_id = stoull(app_idStr.c_str());
			break;
		}
		catch (invalid_argument) {
			PrintErr("Integer Only");
			cout << endl;
		}
	}

	Act["Application_ID"] = app_id; // Add app ID to constructing JSON.

	// Initialize details with user input.
	string details;
	GetInput("Enter Activity Details Text: ", &details);
	Act["Details"] = details;

	// Initialize state with user input.
	string state;
	GetInput("Enter Activity State Text: ", &state);
	Act["State"] = state;

	// Initialize timestamp with user input.
	bool hasTimeStamp;
	while (true) {
		string hasTimeStampStr;
		GetInput("Activity Has Time Stamp ?(Y/n)", &hasTimeStampStr);

		// Validate user input.
		if (hasTimeStampStr == "Y" || hasTimeStampStr == "y") {
			hasTimeStamp = true;
			break;
		}
		else if (hasTimeStampStr == "N" || hasTimeStampStr == "n") {
			hasTimeStamp = false;
			break;
		}
		else {
			PrintErr(" Only (Y/N) or (y/n)");
			cout << endl;
		}
	}

	Act["HasTimeStamp"] = hasTimeStamp; // Add timestamp to constructing JSON.

	// Initialize images & texts with user input.
	string large_image;
	GetInput("Enter Large Image Name: ", &large_image);
	Act["LargeImage"] = large_image;

	string large_text;
	GetInput("Enter Large Image Hover Text: ", &large_text);
	Act["LargeText"] = large_text;

	string small_image;
	GetInput("Enter Small Image Name: ", &small_image);
	Act["SmallImage"] = small_image;

	string small_text;
	GetInput("Enter Small Image Hover Text: ", &small_text);
	Act["SmallText"] = small_text;

	// Add activity to config file.
	CfgMgr->AddActivity(&Act);
}

// Launchs activity from discord library.
void UActivityManager::LaunchActivity(Activity* activity) {

	ClientId app_id = activity->GetApplicationId(); // Set app ID.
	Core* core{}; // Define core.
	Core::Create(app_id, DiscordCreateFlags_Default, &core); // Initialize core.
	ActivityManager& Actman = core->ActivityManager(); // Get activity manager.
	Actman.UpdateActivity(*activity, Callback); // Update Activities.

	while (true) {
		core->RunCallbacks(); // Run Launcher.
		Sleep(100); // Avoid Crashing.
	}
}

// handles callback from UActivityManager::LaunchActivity.
void Callback(Result res) {
	ClearEnv();

	// Check if successful.
	if ((int)res == 0) {
		PrintSuc("Successfully Launched RPC ( Activity )");
		cout << endl;
		PrintWarn("If You Close This Application, Activity Will Gone!");
	}
	else {
		ostringstream ss;
		ss << "Error Occured While Launching Activity...";
		ss << "\n\tPlease Report Me This Error Code: ";
		ss << (int)res;
		PrintErr(ss.str().c_str());
	}
}
