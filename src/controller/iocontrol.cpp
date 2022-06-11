#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>

#include <nlohmann/json.hpp>
#include "controller/iocontrol.h"

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
	for (unsigned int i = 0; i < size; i++) {
		cout << endl << "    [" << CYAN << i + 1 << RESET << "] " << (* options)[i] << endl;
	}
	cout << endl;
}

void io::GetInput(const char* message, string* result) {
	cout << endl << "  [" << BLUE << "?" << RESET << "] " << message;
	getline(cin, *result);
}

void io::PrintBanner() {
	cout << BOLDRED << "\t\t ______  _                            _   _____ ______  _   __  _____              _" << endl;
	cout << "\t\t |  _  \\(_)                          | | /  ___||  _  \\| | / / |_   _|            | |" << endl;
	cout << "\t\t | | | | _  ___   ___  ___   _ __  __| | \\ `--. | | | || |/ /    | |  ___    ___  | | ___" << endl;
	cout << "\t\t | | | || |/ __| / __|/ _ \\ | '__|/ _` |  `--. \\| | | ||    \\    | | / _ \\  / _ \\ | |/ __|" << endl;
	cout << "\t\t | |/ / | |\\__ \\| (__| (_) || |  | (_| | /\\__/ /| |/ / | |\\  \\   | || (_) || (_) || |\\__ \\" << endl;
	cout << "\t\t |___/  |_||___/ \\___|\\___/ |_|   \\__,_| \\____/ |___/  \\_| \\_/   \\_/ \\___/  \\___/ |_||___/" << endl;
	cout << endl << "\t\t\t\t\t    " << BOLDCYAN << "--== Made By iHapiW ==--" << RESET << endl;
}

 void io::ActivitytoStr(json* activity, string* result) {
	stringstream stream;
	vector<string> tmp;

	io::ActivitytoVectStr(activity, &tmp);
	for (auto iter = tmp.begin(); iter != tmp.end(); iter++) {
		stream << *iter << "\n\t";
	}
	stream << "\n\n\t" << BOLDBLUE <<"----------------------------------------\n" << RESET;
	*result = stream.str();
}

 void io::ActivitytoVectStr(json* activity, vector<string>* result) {
	 stringstream stream;
	 result->clear();
	 stream << YELLOW << " Application_ID" << RESET << ":    ";
	 stream << GREEN << (*activity)["Application_ID"] << RESET;
	 result->push_back(stream.str());
	 stream.str(string());
	 stream << YELLOW << " Details" << RESET << ":          ";
	 stream << GREEN << (*activity)["Details"] << RESET;
	 result->push_back(stream.str());
	 stream.str(string());
	 stream << YELLOW << " State" << RESET << ":            ";
	 stream << GREEN << (*activity)["State"] << RESET;
	 result->push_back(stream.str());
	 stream.str(string());
	 stream << YELLOW << " HasTimeStamp" << RESET << ":      ";
	 stream << GREEN << (*activity)["HasTimeStamp"] << RESET;
	 result->push_back(stream.str());
	 stream.str(string());
	 stream << YELLOW << " LargeImage" << RESET << ":       ";
	 stream << GREEN << (*activity)["LargeImage"] << RESET;
	 result->push_back(stream.str());
	 stream.str(string());
	 stream << YELLOW << " LargeText" << RESET << ":        ";
	 stream << GREEN << (*activity)["LargeText"] << RESET;
	 result->push_back(stream.str());
	 stream.str(string());
	 stream << YELLOW << " SmallImage" << RESET << ":       ";
	 stream << GREEN << (*activity)["SmallImage"] << RESET;
	 result->push_back(stream.str());
	 stream.str(string());
	 stream << YELLOW << " SmallText" << RESET << ":        ";
	 stream << GREEN << (*activity)["SmallText"] << RESET;
	 result->push_back(stream.str());
	 stream.str(string());
 }

 void io::ClearEnv() {
	 system("cls");
	 io::PrintBanner();
 }