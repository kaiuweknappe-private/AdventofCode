#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <math.h>
#include <unordered_map>
#include "InputSetup.h"


namespace D04 {

	bool match(const std::vector<int>& winNumbers, int givenNum) {
		for (auto num : winNumbers) {
			if (num == givenNum)
				return true;
		}
		return false;
	}

	void part1() {
		auto file = InputSetup::getFile("input4.txt");
		std::string line, firstLine, secondLine;
		size_t firstPos, middlePos, lastPos;
		std::vector<int> winNumbers, givenNumbers;
		int matches, cardValue, sumCardValues(0);

		//phrase Numbers
		getline(file, line);
		firstPos = line.find(':');
		middlePos = line.find('|');
		lastPos = std::string::npos;
		do{
			//reset Vek
			winNumbers.clear();
			givenNumbers.clear();
			firstLine = line.substr(firstPos + 1, middlePos - firstPos - 1);
			secondLine = line.substr(middlePos + 1, line.size() - middlePos);
			//std::cout << firstLine << std::endl;
			// phrase win Numbers
			size_t lasti(0);
			for (size_t i = 3; i < firstLine.length(); i += 3)	{
				winNumbers.push_back(stoi(firstLine.substr(lasti, 3)));
				lasti = i;
			}
			//phrase given numbers
			lasti = 0;
			for (size_t i = 3; i <= secondLine.length(); i += 3) {
				givenNumbers.push_back(stoi(secondLine.substr(lasti, 3)));
				lasti = i;
			}

			// evaluate card
			matches = 0;
			for(auto num : givenNumbers ) {
				if (match(winNumbers, num)) {
					matches++;
				}
			}
			
			cardValue = 0;
			if (matches > 0) {
				cardValue = 1;
				for (int m = 2; m <= matches; m++) {
					cardValue *= 2;
				}
			}
			std::cout << cardValue << std::endl;
			sumCardValues += cardValue;

		} while (getline(file, line));

		std::cout << sumCardValues;
	}


	void part2() {
		auto file = InputSetup::getFile("input4.txt");
		std::string line, firstLine, secondLine;
		size_t firstPos, middlePos, lastPos;
		std::vector<int> winNumbers, givenNumbers;
		int matches, sumCardTotal(0), cardNum(0);
		struct Card {
			int matches;
			int totalCopies;
		};
		std::unordered_map < int, Card > cards;

		//phrase Numbers
		getline(file, line);
		firstPos = line.find(':');
		middlePos = line.find('|');
		lastPos = std::string::npos;
		do {
			cardNum++;
			//reset Vek
			winNumbers.clear();
			givenNumbers.clear();
			firstLine = line.substr(firstPos + 1, middlePos - firstPos - 1);
			secondLine = line.substr(middlePos + 1, line.size() - middlePos);
			// phrase win Numbers
			size_t lasti(0);
			for (size_t i = 3; i < firstLine.length(); i += 3) {
				winNumbers.push_back(stoi(firstLine.substr(lasti, 3)));
				lasti = i;
			}
			//phrase given numbers
			lasti = 0;
			for (size_t i = 3; i <= secondLine.length(); i += 3) {
				givenNumbers.push_back(stoi(secondLine.substr(lasti, 3)));
				lasti = i;
			}

			// evaluate card
			matches = 0;
			for (auto num : givenNumbers) {
				if (match(winNumbers, num)) {
					matches++;
				}
			}

			//add a new card
			cards[cardNum] = { matches, 1 };
			
		} while (getline(file, line));
	
		//add all copies and count them
		for (int i = 1; i <= cards.size(); i++) {
	
			sumCardTotal += cards[i].totalCopies;
	
			for (int m = 1; m <= cards[i].matches ; m++) {
	
				cards[i + m].totalCopies += cards[i].totalCopies;
			}
		}

		std::cout << sumCardTotal << std::endl;
	}

}
