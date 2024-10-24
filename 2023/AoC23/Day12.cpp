#include <iostream>
#include <fstream>
#include <string>
#include "InputSetup.h"
#include <vector>

namespace D12 {
	size_t getPosofInterval(const std::string& springs, size_t startPos) {

		//return npos if not possible
		return std::string::npos;
	}

	void part1() {
		//read input
		auto file = InputSetup::getFile("test.txt");
		struct Row {
			std::string springs;
			std::vector<int> intervals;
		};
		std::vector<Row> rows;
		std::string line;
		while (getline(file, line)) {
			Row temp;
			temp.springs = line.substr(0, line.find(' '));
			for (size_t i = line.find(' '); i != std::string::npos; i = line.find(',', i+1) ) {
				temp.intervals.push_back(stoi(line.substr(i+1)));
			}
			rows.push_back(temp);
		}
		
		//count arrangements
		int diffArangements{ 0 };
		for (auto& row : rows) {
			for (size_t i = 0; i < row.springs.size(); i++) {
				size_t temp{ 0 };
				for (int x = 0; x < row.intervals.size() - 1; x++)
					temp = getPosofInterval(row.springs, temp);
			
				//jetzt von hinten aufrollen
				for (auto it = std::prev(row.intervals.end()); it != row.intervals.begin(); it--) {
					for (auto itr = it; itr != row.intervals.end(); itr++) {

					}
				}
			}
		}

		std::cout << diffArangements;
	}

	void part2() {
		auto file = InputSetup::getFile("input1.txt");

	}

}
