#include <stdlib.h>
#include <vector>
#include <Windows.h>
#include <sstream>
#include <fstream>

#include "nlohmann/json.hpp"
#include "discord-files/discord.h"

#include "UserActivityManager.h"
#include "iocontrol.h"

static char* CONFIGFILE = strcat(getenv("APPDATA"),"\\DiscordSDKTools\\config.json");

using namespace io;
using namespace std;
using namespace nlohmann;
using namespace discord;

void AddActivity();
void ListActivities();
void Callback(Result);
void ConfigActivity(json*, Activity*);
void RemoveActivity();
void RunActivity();

void UActivityManager::run() {
	system("cls");
	PrintBanner();
	vector<string> options = {"Launch Activity", "List Activites",
		"Remove Activity", "Add Activity"};
	PrintOptions(&options);

	string choiceStr;
	GetInput("Select: ", &choiceStr);
	int choice = atoi(choiceStr.c_str());
	
	switch (choice) {
	case 1:
		RunActivity();
		break;
	case 2:
		ListActivities();
		break;
	case 3:
		RemoveActivity();
		break;
	case 4:
		AddActivity();
		break;
	default:
		PrintErr("Invalid Option!");
		cin.get();
		return;
	}
}

void RunActivity() {
	system("cls");
	PrintBanner();
	vector<json> activities = UActivityManager::ConfigManager::ListActivities();
	json activity;
	vector<string> messages;
	for (int i = 0; i < activities.size(); i++) {
		messages.push_back(PrintActivity(&activities[i]));
	}
	PrintOptions(&messages);
	string resultStr;
	GetInput("Select One to Launch: ", &resultStr);
	size_t result = atoi(resultStr.c_str()) - 1;
	if (result > activities.size() || result < 0) {
		PrintErr("Option Out of Range.");
		cin.get();
		return;
	}
	else {
		json Config = activities[result];
		Activity Act;
		ConfigActivity(&Config, &Act);
		UActivityManager::ConfigManager::LaunchActivity(&Act);
	}
}

void ConfigActivity(json* Config, Activity* act) {

	//Config State & Details
	int64_t App_ID = (int64_t)(*Config)["Application_ID"];
	string state = (string)(*Config)["State"];
	string details = (string)(*Config)["Details"];

	act->SetApplicationId(App_ID);
	act->SetType(ActivityType::Playing);
	act->SetState(state.c_str());
	act->SetDetails(details.c_str());

	//Config TimeStamp
	bool timestamp = (bool)(*Config)["HasTimeStamp"];
	if (timestamp) {
		time_t nowStamp;
		time(&nowStamp);

		ActivityTimestamps* stamps = &act->GetTimestamps();
		stamps->SetStart(nowStamp);
		stamps->SetEnd(0);
	}

	//Config Assets
	string large_image = (string)(*Config)["LargeImage"];
	string large_text = (string)(*Config)["LargeText"];
	string small_image = (string)(*Config)["SmallImage"];
	string small_text = (string)(*Config)["SmallText"];
	ActivityAssets* assets = &act->GetAssets();
	assets->SetLargeImage(large_image.c_str());
	assets->SetLargeText(large_text.c_str());
	assets->SetSmallImage(small_image.c_str());
	assets->SetSmallText(small_text.c_str());

	//Config Party
	ActivityParty* party = &act->GetParty();
	party->SetId("");
	PartySize* size = &party->GetSize();
	size->SetCurrentSize(0);
	size->SetMaxSize(0);

	//Config Secrets
	ActivitySecrets* secrets = &act->GetSecrets();
	secrets->SetJoin("");
	secrets->SetMatch("");
	secrets->SetSpectate("");

	//Config Instance
	act->SetInstance(true);
}

void RemoveActivity() {
	system("cls");
	PrintBanner();
	vector<json> activities = UActivityManager::ConfigManager::ListActivities();
	json activity;
	vector<string> messages;
	for (int i = 0; i < activities.size(); i++) {
		messages.push_back(PrintActivity(&activities[i]));
	}
	PrintOptions(&messages);
	string resultStr;
	GetInput("Select One to Remove: ", &resultStr);
	size_t result = atoi(resultStr.c_str()) - 1;
	if (result > activities.size() || result < 0) {
		PrintErr("Option Out of Range.");
		cin.get();
		return;
	}
	else {
		json activity = activities[result];
		UActivityManager::ConfigManager::RemoveActivity(&activity);
		ostringstream ss;
		ss << "Successfully Deleted ";
		ss << activity["Application_ID"];
		PrintSuc(ss.str().c_str());
		cin.get();
	}
}

void ListActivities() {
	system("cls");
	PrintBanner();
	vector<json> activities = UActivityManager::ConfigManager::ListActivities();
	json activity;
	vector<string> messages;
	for (int i = 0; i < activities.size(); i++) {
		messages.push_back(PrintActivity(&activities[i]));
	}
	PrintOptions(&messages);
	cin.get();
}

void AddActivity() {
	system("cls");
	PrintBanner();

	json Act;
	uint64_t app_id;
	while (true) {
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

	Act["Application_ID"] = app_id;

	// State & Details
	string state;
	GetInput("Enter Activity State Text: ", &state);
	Act["State"] = state;

	string details;
	GetInput("Enter Activity Details Text: ", &details);
	Act["Details"] = details;

	// TimeStamp
	bool hasTimeStamp;
	while (true) {
		string hasTimeStampStr;
		GetInput("Activity Has Time Stamp ?(Y/n)", &hasTimeStampStr);

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
	Act["HasTimeStamp"] = hasTimeStamp;

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

	UActivityManager::ConfigManager::AddActivity(&Act);
}

void UActivityManager::ConfigManager::AddActivity(json* Activity) {
	fstream ConfigFile;
	ConfigFile.open(CONFIGFILE, ios::in);
	json Config;
	
	try {
		Config = json::parse(ConfigFile);
	}
	catch (json::parse_error) {
		Config = json::array();
	}

	Config.insert(Config.begin(), *Activity);
	ConfigFile.close();
	
	ConfigFile.open(CONFIGFILE, ios::out);
	ConfigFile << Config;
	ConfigFile.close();
}

vector<json> UActivityManager::ConfigManager::ListActivities() {
	fstream ConfigFile;
	ConfigFile.open(CONFIGFILE, ios::in);
	json Config;
	try {
		Config = json::parse(ConfigFile);
	}
	catch (json::parse_error) {
		Config = json::array();
	}
	ConfigFile.close();
	vector<json> result;
	for (int i = 0; i < Config.size(); i++) {
		result.push_back(Config[i]);
	}
	return result;
}

void UActivityManager::ConfigManager::RemoveActivity(json* activity) {
	fstream ConfigFile;
	ConfigFile.open(CONFIGFILE, ios::in);
	json Config;
	try {
		Config = json::parse(ConfigFile);
	}
	catch (json::parse_error) {
		Config = json::array();
	}
	ConfigFile.close();
	for (int i = 0; i < Config.size(); i++) {
		json existActivity = Config[i];
		if (existActivity == *activity) {
			Config.erase(i);
		}
	}

	ConfigFile.open(CONFIGFILE, ios::out);
	ConfigFile << Config.dump();
	ConfigFile.close();
}

void UActivityManager::ConfigManager::LaunchActivity(Activity* Act) {
	ClientId app_id = Act->GetApplicationId();
	Core* core{};
	Core::Create(app_id, DiscordCreateFlags_Default, &core);
	ActivityManager& Actman = core->ActivityManager();
	Actman.UpdateActivity(*Act, Callback);

	while (true) {
		core->RunCallbacks();
		Sleep(100);
	}
}

void Callback(Result res) {
	system("cls");
	PrintBanner();
	if ((int)res == 0) {
		PrintSuc("Successfully Launched RPC ( Activity )");
		cout << endl;
		PrintWarn("If You Close This Application, Activity Will Gone!");
	}
	else {
		ostringstream ss;
		ss << "Error Occured While Launching Activity...";
		ss << "\n\tPlease Report me This Error Code: ";
		ss << (int)res;
		PrintErr(ss.str().c_str());
	}
}