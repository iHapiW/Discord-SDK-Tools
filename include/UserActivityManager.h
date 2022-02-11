#pragma once


#include "discord-files/discord.h"
#include <nlohmann/json.hpp>
#include <vector>
#include "iocontrol.h"

namespace UActivityManager {
	class ConfigManager {
	public:
		static std::vector<nlohmann::json> ListActivities();
		static void RemoveActivity(nlohmann::json* activity);
		static void AddActivity(nlohmann::json* activity);
		static void LaunchActivity(discord::Activity*);
	};
	void run();
}