#pragma once

#include <nlohmann/json.hpp>
#include "discord-files/discord.h"

#include "iocontrol.h"

namespace UActivityManager {
	void LaunchActivity(discord::Activity* activity);
	void run();
}