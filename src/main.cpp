#include <iostream>
#include <vector>

#include <nlohmann/json.hpp>
#include "discord-files/discord.h"

#include "controller/iocontrol.h"
#include "controller/ActivityController.h"

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
            ActivityController::run();
            break;
        default:
            PrintErr("Invalid Option.");
            cin.get();
        }
    }

    return 0;
}