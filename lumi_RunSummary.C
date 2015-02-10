// string::find_last_of
#include <iostream>       // std::coout
#include <fstream>
#include <string>         // std::string

float lumi_RunSummary()
{
	std::string str1 ("?RUN=");
	std::string str2 ("RunSummary.html");
	ifstream inFile("RunSummary.html");
	//std::string str1 ("runNumber");
	//std::string str2 ("PageZero.xml");
	//ifstream inFile("PageZero.xml");
	if (!inFile) {
		cerr << "File RunSummary.html not found." << endl;
		return -1;
	}
	// Using getline() to read one line at a time.
	string line;
	while (getline(inFile, line)) {
		if (line.empty()) continue;
		std::cout << "Finding: " << str1 <<" In: "<<str2<<'\n';
		std::size_t found = line.rfind(str1);
		if (found!=std::string::npos){
			unsigned found_begin = line.find("RUN=");
			std::string str_a=line.substr(found_begin+4);
			std::cout<<"String A: "<<str_a<<std::endl;
			unsigned found_end = str_a.find("&DB");
			std::string value_str = str_a.substr(0,found_end);
			std::cout<<"String value: "<<value_str<<std::endl;
			const char *cstr = value_str.c_str();
			float value =atof(cstr);
			std::cout<<"Float value: "<<value<<std::endl;
			return value;
		}
	}
	return -1;
}
