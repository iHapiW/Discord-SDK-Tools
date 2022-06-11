#include <string>
#include <iostream>
#include <sstream>

#include <nlohmann/json.hpp>
#include "discord-files/discord.h"

#include "controller/ActivityController.h"
#include "model/UserActivityManager.h"
#include "controller/iocontrol.h"

using namespace std;
using namespace io;
using namespace nlohmann;
using namespace discord;

// This function executes from main file, when user selects.
void ActivityController::run() {
	ClearEnv();

	// Initialize Config Manager
	UActivityManager::ConfigManager CfgMgr;

	// List & Print Options.
	vector<string> options = { "Add Activity", "Remove Activity", "Modify Activity",
		"Show Listed Activites" ,"Launch Activity" };
	PrintOptions(&options);

	// Get input from options.
	string choiceStr;
	GetInput("Select: ", &choiceStr);
	int choice = atoi(choiceStr.c_str());

	// Validate input & handle.
	switch (choice) {
	case 1:
		ActivityController::AddActivity(&CfgMgr);
		break;
	case 2:
		ActivityController::RemoveActivity(&CfgMgr);
		break;
	case 3:
		ActivityController::ModifyActivity(&CfgMgr);
		break;
	case 4:
		ActivityController::ShowActivities(&CfgMgr);
		break;
	case 5:
		ActivityController::LaunchActivity(&CfgMgr);
		break;
	default:
		PrintErr("Invalid Option!");
		cin.get();
		return;
	}
}

// Lists activities and asks user to select one with specified question
// Returns 1 if successfully got 
bool ActivityController::SelectAct(UActivityManager::ConfigManager* CfgMgr, string question = "", json* Config = new json) {

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

// This function executes from ActivityController::run(), when user selects.
void ActivityController::AddActivity(UActivityManager::ConfigManager* CfgMgr) {
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

// This function executes from UActivityManager::run(), when user selects.
void ActivityController::RemoveActivity(UActivityManager::ConfigManager* CfgMgr) {
	ClearEnv();
	json Config;
	bool res = ActivityController::SelectAct(CfgMgr, "Select One to Remove: ", &Config);
	if (!res) return;

	CfgMgr->RemoveActivity(&Config); // Remove activity from config.
	ostringstream ss;
	ss << "Successfully Deleted ";
	ss << Config["Application_ID"] << ".";
	PrintSuc(ss.str().c_str());
	cin.get();
}

// This function executes from ActivityController::run(), when user selects.
void ActivityController::ModifyActivity(UActivityManager::ConfigManager* CfgMgr) {
	json OldConfig;
	json NewConfig;
	string choiceStr;
	int choice;
	int OldIndex = 0;
	vector<string> options;
	json FullConfig;

	// Select modifying activity
	ClearEnv();
	bool res = ActivityController::SelectAct(CfgMgr, "Select One to Modify: ", &OldConfig);
	if (!res) return;

	// List activity object children & Get input about which to modify.
	ClearEnv();
	ActivitytoVectStr(&OldConfig, &options);
	PrintOptions(&options);

	GetInput("Enter One to Modify: ", &choiceStr);
	choice = stoi(choiceStr);

	if (choice < 1 || choice > 8) {
		PrintErr("Option Out of Range.");
		cin.get();
		return;
	}

	NewConfig = OldConfig;
	GetInput("Enter New Value: ", &choiceStr);

	switch (choice) {
	case 1:
		while (true) {
			try {
				NewConfig["Application_ID"] = stoull(choiceStr.c_str());
				break;
			}
			catch (invalid_argument) {
				PrintErr("Integer Only.");
				cout << endl;
				GetInput("Enter New Value: ", &choiceStr);
			}
		}
		break;
	case 2:
		NewConfig["Details"] = choiceStr;
		break;
	case 3:
		NewConfig["State"] = choiceStr;
		break;
	case 4:
		while (true) {
			if (choiceStr == "Y" || choiceStr == "y") {
				NewConfig["HasTimeStamp"] = true;
				break;
			}
			else if (choiceStr == "N" || choiceStr == "n") {
				NewConfig["HasTimeStamp"] = false;
				break;
			}
			else {
				PrintErr("Only(Y / N) or (y / n)");
				cout << endl;
				GetInput("Enter New Value: ", &choiceStr);
			}
		}
		break;
	case 5:
		NewConfig["LargeImage"] = choiceStr;
		break;
	case 6:
		NewConfig["LargeText"] = choiceStr;
		break;
	case 7:
		NewConfig["SmallImage"] = choiceStr;
		break;
	case 8:
		NewConfig["SmallText"] = choiceStr;
		break;
	};

	FullConfig = CfgMgr->GetConfig();

	for (int i = 0; i < FullConfig.size(); i++) {
		if (OldConfig == FullConfig[i]) {
			OldIndex = i;
		}
	}

	FullConfig.erase(OldIndex);
	FullConfig.insert(FullConfig.begin()+OldIndex, NewConfig);

	CfgMgr->SetConfig(&FullConfig);

	PrintSuc("Operation Done Successfully.");

	cin.get();
}

// This function executes from ActivityController::run(), when user selects.
void ActivityController::ShowActivities(UActivityManager::ConfigManager* CfgMgr) {
	ClearEnv();
	ActivityController::SelectAct(CfgMgr);
}

// Configures Activity from json ( json constructed by other functions, from input ).
void ActivityController::ConfigActivity(json* Config, Activity* act) {

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
	ActivityTimestamps* stamps = &act->GetTimestamps();
	if (timestamp) {
		time_t nowStamp;
		time(&nowStamp);

		stamps->SetStart(nowStamp);
		stamps->SetEnd(0);
	}
	else {
		stamps->SetStart(0);
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

// This function executes from ActivityController::run(), when user selects.
void ActivityController::LaunchActivity(UActivityManager::ConfigManager* CfgMgr) {
	ClearEnv();
	json Config;
	bool res = ActivityController::SelectAct(CfgMgr, "Select One to Launch: ", &Config);
	if (!res) return;

	Activity Act;
	ConfigActivity(&Config, &Act); // Configure activity from json.
	UActivityManager::LaunchActivity(&Act); // Launchs activity.
}