#pragma once

#include <fstream>
#include <iostream>

class InputSetup
{
public:
	
	static auto getFile(const char* name) {
		std::ifstream file(name);

		if (!file.is_open()) {
			std::cout << "coudn't open file" << std::endl;
			std::ifstream emptyfile;
			return emptyfile;
		}

		return file;
	}

};
