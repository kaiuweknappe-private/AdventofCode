#include <iostream>
#include <fstream>
#include <string>
#include "InputSetup.h"
#include <unordered_map>

namespace D09 {

	bool isZero(const std::unordered_map<int, int>& set) {
		for (const auto& val : set) {
			if (val.second != 0)
				return false;
		}
		return true;
	}

	void part1() {
		auto file = InputSetup::getFile("input9.txt");

		std::string line;
		std::unordered_map<int, std::unordered_map<int, int>> dataset;
		int sum{ 0 };
		while (getline(file, line)) {
			//reset dataset
			dataset.clear();
			//read dataset input
			int i = 0;
			for (size_t pos = 0; pos < line.size(); i++, pos = line.find(" ", pos + 1)) {
				dataset[0][i] = stoi(line.substr(pos));
			}

			int setNum{ 0 };
			while (!isZero(dataset[setNum])) {
				//then new set to dataset
				for (int i = 0; i < dataset[setNum].size() - 1; i++) {
					dataset[setNum + 1][i] = dataset[setNum][i + 1] - dataset[setNum][i];
				}
				setNum++;
			}

			//extraprolate
			dataset[setNum][dataset[setNum].size()] = 0;
			for (int i = setNum-1; i >= 0; i--) {
				int appendPos = dataset[i].size();
				dataset[i][appendPos] = dataset[i][appendPos - 1] + dataset[i + 1][appendPos - 1];
			}
			
			sum += dataset[0][dataset[0].size() - 1];
		}

		std::cout << sum;
	}

	void part2() {
		auto file = InputSetup::getFile("input9.txt");

		std::string line;
		std::unordered_map<int, std::unordered_map<int, int>> dataset;
		int sum{ 0 };
		while (getline(file, line)) {
			//reset dataset
			dataset.clear();
			//read dataset input
			int i = 0;
			for (size_t pos = 0; pos < line.size(); i++, pos = line.find(" ", pos + 1)) {
				dataset[0][i] = stoi(line.substr(pos));
			}

			int setNum{ 0 };
			while (!isZero(dataset[setNum])) {
				//then new set to dataset
				for (int i = 0; i < dataset[setNum].size() - 1; i++) {
					dataset[setNum + 1][i] = dataset[setNum][i + 1] - dataset[setNum][i];
				}
				setNum++;
			}

			//extraprolate
			dataset[setNum][-1] = 0;
			for (int i = setNum - 1; i >= 0; i--) {
				
				dataset[i][-1] = dataset[i][0] - dataset[i + 1][-1];
			}

			sum += dataset[0][-1];
		}

		std::cout << sum;
	}

}
