#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

#include "nlohmann/json.hpp"
#include "iocontrol.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using namespace std;
using namespace nlohmann;

void io::PrintWarn(const char* message) {
	cout << endl << "  [" << YELLOW << "*" << RESET << "] " << message;
}

void io::PrintSuc(const char* message) {
	cout << endl << "  [" << GREEN << "+" << RESET << "] " << message;
}

void io::PrintErr(const char* message) {
	cout << endl << "  [" << RED << "-" << RESET << "] " << message;
}

void io::PrintOptions(vector<string>* options) {
	size_t size = options->size();
	for (int i = 0; i < size; i++) {
		cout << endl << "     [" << CYAN << i + 1 << RESET << "] " << (* options)[i] << endl;
	}
	cout << endl;
}

void io::GetInput(const char* message, string* result) {
	cout << endl << "  [" << BLUE << "?" << RESET << "] " << message;
	getline(cin, *result);
}

void io::PrintBanner() {
	cout << BOLDRED << "\t  _____  _                       _  _____ _____  _  _________          _     \n";
	cout << "\t |  __ \\(_)                     | |/ ____|  __ \\| |/ /__   __|        | |    \n";
	cout << "\t | |  | |_ ___  ___ ___  _ __ __| | (___ | |  | | ' /   | | ___   ___ | |___ \n";
	cout << "\t | |  | | / __|/ __/ _ \\| '__/ _` |\\___ \\| |  | |  <    | |/ _ \\ / _ \\| / __|\n";
	cout << "\t | |__| | \\__ \\ (_| (_) | | | (_| |____) | |__| | . \\   | | (_) | (_) | \\__ \\\n";
	cout << "\t |_____/|_|___/\\___\\___/|_|  \\__,_|_____/|_____/|_|\\_\\  |_|\\___/ \\___/|_|___/\n\n\t\t\t\t" << CYAN << "--== Made By iHapiW ==--" << RESET << endl;
}

string io::PrintActivity(json* activity) {
	ostringstream stream;
	stream << "Application ID:    ";
	stream << GREEN << (* activity)["Application_ID"] << RESET;
	stream << "\n\t Activity Details: ";
	stream << GREEN << (* activity)["Details"] << RESET;
	stream << "\n\t Activity State:   ";
	stream << GREEN << (* activity)["State"] << RESET;
	stream << "\n\t Has Time Stamp:    ";
	stream << GREEN << (* activity)["HasTimeStamp"] << RESET;
	stream << "\n\n\t Activity Large Image:\n\n\t     Name:        ";
	stream << GREEN << (* activity)["LargeImage"] << RESET;
	stream << "\n\t     Hover Text:  ";
	stream << GREEN << (* activity)["LargeText"] << RESET;
	stream << "\n\n\t Activity Small Image:\n\n\t     Name:        ";
	stream << GREEN << (* activity)["SmallImage"] << RESET;
	stream << "\n\t     Hover Text:  ";
	stream << GREEN << (* activity)["SmallText"] << RESET;
	stream << "\n\n\t" << MAGENTA <<"----------------------------------------\n" << RESET;
	return stream.str();
}