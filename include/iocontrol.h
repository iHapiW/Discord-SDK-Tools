#pragma once

#include <iostream>
#include <string.h>

#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

namespace io {
	void PrintWarn(const char* message);
	void PrintSuc(const char* message);
	void PrintErr(const char* message);
	void PrintOptions(vector<string>* options);
	void GetInput(const char* message, string* result);
	void PrintBanner();
	string PrintActivity(json* activity);
}

//[{"Application_ID":926042507907837993,"Details":"Launching it...","HasTimeStamp":true,"LargeImage":"cpp","LargeText":"C++ Logo","SmallImage":"apadama","SmallText":"Apadama Team Logo","State":"Working On DiscordSDK Tools"}]