#include <fstream>

#include <nlohmann/json.hpp>

#include "ConfigManager.h"

using namespace std;
using namespace nlohmann;

// Lists activities into vector & returns.
void UActivityManager::ConfigManager::ListActivities(vector<json>* result) {
	json Config = GetConfig();
	for (unsigned int i = 0; i < Config.size(); i++) {
		result->push_back(Config[i]);
	}
}

// removes activity as json from config file.
void UActivityManager::ConfigManager::RemoveActivity(json* activity) {
	json Config = GetConfig();

	// Iterate over activities inside config, remove selected one.
	for (unsigned int i = 0; i < Config.size(); i++) {
		json existActivity = Config[i];
		if (existActivity == *activity) {
			Config.erase(i);
		}
	}

	SetConfig(&Config);
}

// Adds activity as json to config file.
void UActivityManager::ConfigManager::AddActivity(json* Activity) {
	json Config = GetConfig();
	Config.insert(Config.begin(), *Activity);
	SetConfig(&Config);
}

json UActivityManager::ConfigManager::GetConfig() {
	// Open config file.
	fstream ConfigFile(CONFIGFILE, ios::in);

	// Parse config as json or make new one.
	json Config;
	try {
		Config = json::parse(ConfigFile);
	}
	catch (json::parse_error tst) {
		Config = json::array();
	}
	ConfigFile.close();

	return Config;

}

void UActivityManager::ConfigManager::SetConfig(nlohmann::json* config) {
	// write data inside config file.
	fstream ConfigFile(CONFIGFILE, ios::out);
	ConfigFile << config->dump();
	ConfigFile.close();
}
