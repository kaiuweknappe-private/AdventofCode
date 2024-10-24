#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "InputSetup.h"

namespace D01 {

	void part1() {
		auto file = InputSetup::getFile("input1.txt");

		std::string line, temp;
		char const* digits = "0123456789";
		std::vector < std::string > numVek;

		while (getline(file, line)) {
			temp = "";
			temp.push_back(line.at(line.find_first_of(digits)));
			temp.push_back(line.at(line.find_last_of(digits)));
			numVek.push_back(temp);
		}

		int sum(0);
		for (std::string element : numVek) {
			sum += std::stoi(element);
		}

		std::cout << sum << std::endl;
	}

	void part2() {
		std::ifstream file = InputSetup::getFile("input1.txt");

		std::string line, temp;
		char const* digits = "0123456789";
		std::vector < std::string > numVek;
		size_t firstPos, lastPos, tempPos;
		std::string lastNum;



		while (getline(file, line)) {
			temp = "";

			firstPos = line.find_first_of(digits);
			if (firstPos != std::string::npos) { temp = line.at(firstPos); }
			if (line.find("one") < firstPos) { firstPos = line.find("one"); temp = "1"; }
			if (line.find("two") < firstPos) { firstPos = line.find("two"); temp = "2"; }
			if (line.find("three") < firstPos) { firstPos = line.find("three"); temp = "3"; }
			if (line.find("four") < firstPos) { firstPos = line.find("four"); temp = "4"; }
			if (line.find("five") < firstPos) { firstPos = line.find("five"); temp = "5"; }
			if (line.find("six") < firstPos) { firstPos = line.find("six"); temp = "6"; }
			if (line.find("seven") < firstPos) { firstPos = line.find("seven"); temp = "7"; }
			if (line.find("eight") < firstPos) { firstPos = line.find("eight"); temp = "8"; }
			if (line.find("nine") < firstPos) { firstPos = line.find("nine"); temp = "9"; }

			lastPos = line.find_last_of(digits);
			if (lastPos != std::string::npos) { lastNum = line.at(lastPos); }
			else { lastPos = 0; }

			tempPos = line.rfind("one");
			if (tempPos >= lastPos && tempPos != std::string::npos) {
				lastPos = tempPos; lastNum = "1";
			}
			tempPos = line.rfind("two");
			if (tempPos >= lastPos && tempPos != std::string::npos) {
				lastPos = tempPos; lastNum = "2";
			}
			tempPos = line.rfind("three");
			if (tempPos >= lastPos && tempPos != std::string::npos) {
				lastPos = tempPos; lastNum = "3";
			}
			tempPos = line.rfind("four");
			if (tempPos >= lastPos && tempPos != std::string::npos) {
				lastPos = tempPos; lastNum = "4";
			}
			tempPos = line.rfind("five");
			if (tempPos >= lastPos && tempPos != std::string::npos) {
				lastPos = tempPos; lastNum = "5";
			}
			tempPos = line.rfind("six");
			if (tempPos >= lastPos && tempPos != std::string::npos) {
				lastPos = tempPos; lastNum = "6";
			}
			tempPos = line.rfind("seven");
			if (tempPos >= lastPos && tempPos != std::string::npos) {
				lastPos = tempPos; lastNum = "7";
			}
			tempPos = line.rfind("eight");
			if (tempPos >= lastPos && tempPos != std::string::npos) {
				lastPos = tempPos; lastNum = "8";
			}
			tempPos = line.rfind("nine");
			if (tempPos >= lastPos && tempPos != std::string::npos) {
				lastPos = tempPos; lastNum = "9";
			}

			temp.append(lastNum);
			numVek.push_back(temp);
		}

		int sum(0);
		for (std::string element : numVek) {
			sum += std::stoi(element);
		}

		std::cout << sum << std::endl;
	}

}
