#pragma once

#include "discord-files/discord.h"

namespace UActivityManager {
	void LaunchActivity(discord::Activity* activity);
	void Callback(discord::Result res);
}