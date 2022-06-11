#include <vector>
#include <Windows.h>
#include <sstream>

#include "discord-files/discord.h"

#include "model/UserActivityManager.h"
#include "controller/iocontrol.h"

using namespace io;					// iocontro.h, namespace
using namespace discord;			// Discord library namespace

// Launchs activity from discord library.
void UActivityManager::LaunchActivity(Activity* activity) {

	ClientId app_id = activity->GetApplicationId(); // Set app ID.
	Core* core{}; // Define core.
	Core::Create(app_id, DiscordCreateFlags_Default, &core); // Initialize core.
	ActivityManager& Actman = core->ActivityManager(); // Get activity manager.
	Actman.UpdateActivity(*activity, UActivityManager::Callback); // Update Activities.

	while (true) {
		core->RunCallbacks(); // Run Launcher.
		Sleep(100); // Avoid Crashing.
	}
}

// handles callback from UActivityManager::LaunchActivity.
void UActivityManager::Callback(Result res) {
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
