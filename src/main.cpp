#include <iostream>
#include <vector>

#include <nlohmann/json.hpp>
#include "discord-files/discord.h"

#include "iocontrol.h"
#include "UserActivityManager.h"

using namespace std;
using namespace io;

int main() {
    while (true) {
        system("cls");
        PrintBanner();

        vector<string> options = { "Configure Activites."};
        PrintOptions(&options);

        string choice;
        GetInput("Enter Choice: ", &choice);

        switch (atoi(choice.c_str())) {
        case 1:
            UActivityManager::run();
            break;
        default:
            PrintErr("Invalid Option.");
            cin.get();
            exit(1);
        }
    }

    return 0;
}