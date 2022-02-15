#pragma once

#include <cstdlib>
#include <vector>

#include <nlohmann/json.hpp>

static std::string cfg = (std::string)getenv("APPDATA") +
						 "\\DiscordSDKTools\\config.json";

namespace UActivityManager {
	class ConfigManager {
	public:
		ConfigManager();
		void ListActivities(std::vector<nlohmann::json>* result);
		void RemoveActivity(nlohmann::json* activity);
		void AddActivity(nlohmann::json* activity);
		nlohmann::json GetConfig();
		void SetConfig(nlohmann::json* config);
	private:
		const char* CONFIGFILE = cfg.c_str();
	};
}