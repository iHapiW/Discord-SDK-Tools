#pragma once

#include <string>

#include <nlohmann/json.hpp>
#include "discord-files/discord.h"

#include "model/UserActivityManager.h"
#include "model/ConfigManager.h"

using namespace std;
using namespace nlohmann;
using namespace discord;

namespace ActivityController {
	void run();
	bool SelectAct(UActivityManager::ConfigManager* CfgMgr, string question, json* Config);
	void AddActivity(UActivityManager::ConfigManager* CfgMgr);
	void RemoveActivity(UActivityManager::ConfigManager* CfgMgr);
	void ModifyActivity(UActivityManager::ConfigManager* CfgMgr);
	void ShowActivities(UActivityManager::ConfigManager* CfgMgr);
	void ConfigActivity(json*, Activity*);
	void LaunchActivity(UActivityManager::ConfigManager* CfgMgr);
}