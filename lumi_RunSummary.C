// string::find_last_of
#include <iostream>       // std::coout
#include <fstream>
#include <string>         // std::string

float lumi_RunSummary()
{
	std::string str1 ("?RUN=");
	std::string str2 ("RunSummary.html");
	ifstream inFile("RunSummary.html");
	if (!inFile) {
		cerr << "File RunSummary.html not found." << endl;
		return -1;
	}
	// Using getline() to read one line at a time.
	string line;
	while (getline(inFile, line)) {
		if (line.empty()) continue;
		std::size_t found = line.rfind(str1);
		if (found!=std::string::npos){
			unsigned found_begin = line.find("RUN=");
			std::string str_a=line.substr(found_begin+4);
			unsigned found_end = str_a.find("&DB");
			std::string value_str = str_a.substr(0,found_end);
			const char *cstr = value_str.c_str();
			float value =atof(cstr);
			return value;
		}
	}
	return -1;
}
