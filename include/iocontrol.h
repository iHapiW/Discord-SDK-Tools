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
	void ActivitytoStr(json* activity, string* result);
	void ClearEnv();
}