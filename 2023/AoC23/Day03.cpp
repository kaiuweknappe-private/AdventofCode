#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "InputSetup.h"


namespace D03 {

	bool hasSymbol(std::string line, size_t index) {
		//outofbounce catch
		if (index < 0 || index >= line.size())
			return false;
		
		if (line[index] != '.' && !std::isdigit(line[index]))
			return true;

		return false;
	}
	void part1() {
		auto file = InputSetup::getFile("input3.txt");
		std::string currentNum, lastLine, currentLine, nextLine;
		char pointer;
		bool isNum(false);
		int sum(0);

		//init
		getline(file, lastLine);
		getline(file, currentLine);

		//first line check
		for (size_t i = 0; i < lastLine.size(); i++) {
			pointer = lastLine.at(i);

			currentNum = "";
			isNum = false;
			if (std::isdigit(pointer)) {
				//new num

				//front diagonal
				if (hasSymbol(lastLine, i-1)|| hasSymbol(currentLine, i - 1))
					isNum = true;

				for (i; std::isdigit(pointer); i++, pointer = lastLine.at(i)) {
					currentNum.push_back(pointer);
					if (hasSymbol(currentLine, i))
						isNum = true;
					if (i + 1 >= lastLine.size())
						break;
				}

				//back diagonal
				if (hasSymbol(lastLine, i ) || hasSymbol(currentLine, i))
					isNum = true;
			}

			if (isNum) {
				std::cout << stoi(currentNum) << std::endl;
				sum += stoi(currentNum);
			}

		}

		//data check
		while (getline(file, nextLine)) {

			for (size_t i = 0; i < currentLine.size(); i++) {
				pointer = currentLine.at(i);

				currentNum = "";
				isNum = false;
				if (std::isdigit(pointer)) {
					//new num

					//front diagonal
					if (hasSymbol(lastLine, i - 1) || hasSymbol(currentLine, i - 1) || hasSymbol(nextLine, i - 1))
						isNum = true;

					for (i; std::isdigit(pointer); i++, pointer = currentLine.at(i)) {
						currentNum.push_back(pointer);
						if (hasSymbol(lastLine, i) || hasSymbol(nextLine, i))
							isNum = true;
						if (i+1 >= currentLine.size())
							break;
					}

					//back diagonal
					if (hasSymbol(lastLine, i) || hasSymbol(currentLine, i) || hasSymbol(nextLine, i))
						isNum = true;
				}

				if (isNum) {
					std::cout << currentNum << std::endl;
					sum += stoi(currentNum);
				}
				
			}

			lastLine = currentLine;
			currentLine = nextLine;
		}

		//last line check
		for (size_t i = 0; i < currentLine.size(); i++) {
			pointer = currentLine.at(i);

			currentNum = "";
			isNum = false;
			if (std::isdigit(pointer)) {
				//new num

				//front diagonal
				if (hasSymbol(lastLine, i - 1) || hasSymbol(currentLine, i - 1))
					isNum = true;

				for (i; std::isdigit(pointer); i++, pointer = currentLine.at(i)) {
					currentNum.push_back(pointer);
					if (hasSymbol(lastLine, i))
						isNum = true;
					if (i + 1 >= currentLine.size())
						break;						
				}

				//back diagonal
				if (hasSymbol(lastLine, i) || hasSymbol(currentLine, i ))
					isNum = true;
			}

			if (isNum) {
				std::cout << stoi(currentNum) << std::endl;
				sum += stoi(currentNum);
			}

		}

		std::cout << sum << std::endl;
	}

	// part 2
	class Number
	{
	public:
		int line;
		size_t firstPos;
		size_t lastPos;
		int value;

	};

	int legitGear(0);
	std::vector<Number> numbers;

	bool isInRange(size_t gearPos, size_t firstPos, size_t lastPos) {
		for (size_t i = firstPos; i <= lastPos; i++)
		{
			if (i == gearPos - 1 || i == gearPos || i == gearPos + 1)
				return true;
		}
		return false;
	}

	int checkGear(int gearLine, size_t gearPos) {
		legitGear = 0;
		int gearRatio = 1;

		for (const Number& num : numbers) {
			if (num.line == gearLine - 1 || num.line == gearLine || num.line == gearLine + 1) {
				if (isInRange(gearPos, num.firstPos, num.lastPos)) {
					legitGear++;
					//std::cout << num.value << std::endl;
					gearRatio *= num.value;
				}

			} 
		}

		return gearRatio;
	}

	void part2() {
		auto file = InputSetup::getFile("input3.txt");
		Number temp;
		std::string line;
		int lineNum(0);

		//phrase file
		while (getline(file, line)) {
			lineNum++;
			for (size_t i = 0; i < line.length(); i++)	{				
				if (std::isdigit(line[i])) {
					temp.firstPos = i;
					for (i; std::isdigit(line[i]); i++) {
						temp.lastPos = i;
						//std::cout << line[i] << std::endl;
						if (i + 1 >= line.length())
							break;
					}
					if (i >= line.length())
						break;
					temp.value = stoi(line.substr(temp.firstPos, temp.lastPos - temp.firstPos + 1 ));
					//std::cout << temp.value << std::endl;
					temp.line = lineNum;
					numbers.push_back(temp);
				}
			}
		}

		//rest file
		file.close();
		file.open("input3.txt");

		lineNum = 0;
		long gearRatioSum = 0;
		int gearRatio;
		//check every gear *
		while (getline(file, line)) {
			lineNum++;
			for (size_t i = 0; i < line.length(); i++) {
				if (line[i] == '*') {
					//every *
					gearRatio = checkGear(lineNum, i);
					if (legitGear == 2) {
						gearRatioSum += gearRatio;
						//std::cout << "hit" << std::endl;

					}
				}
			}
		}

		std::cout << gearRatioSum << std::endl;
		
	}


}
