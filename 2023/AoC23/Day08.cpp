#include <iostream>
#include <fstream>
#include <string>
#include "InputSetup.h"
#include <unordered_map>
#include <map>


namespace D08 {

	void part1() {
		auto file = InputSetup::getFile("input8.txt");

		//read instructions
		std::string line;
		std::unordered_map<int, char> instructions;
		getline(file, line);
		for (int i{ 0 }; i < line.size(); i++) {
			instructions[i] = line[i];
		}

		//read map
		struct Direction {
			std::unordered_map<std::string, Direction>::iterator left;
			std::unordered_map<std::string, Direction>::iterator right;
		};
		std::unordered_map<std::string, Direction> map;
		getline(file, line);
		while (getline(file, line)) {
			map[line.substr(0, 3)];
		}
		file.close(); file.open("input8.txt");
		getline(file, line); getline(file, line);
		while (getline(file, line)) {
			map[line.substr(0, 3)] = Direction{ map.find(line.substr(7,3)), map.find(line.substr(12,3)) };
		}

		//std::cout << map["AAA"].left->first;
		//std::cout << map["AAA"].right->first;
		//count steps
		int steps{ 0 };
		std::string currentKnot{"AAA"};
		for (int i = 0; i < instructions.size(); i++) {

			steps++;
			//std::cout << currentKnot << ':' << instructions[i] << '(' << map[currentKnot].left->first << '|'<< map[currentKnot].right->first << ')' << '\n';
			if (instructions[i] == 'L') {
				currentKnot = map[currentKnot].left->first; 
			}
			else {
				currentKnot = map[currentKnot].right->first;
			}
	
			if (currentKnot[0] == 'Z') { //should be slighly faster than than == "ZZZ", i guess
				if (currentKnot[1] == 'Z') {
					if (currentKnot[2] == 'Z') {
						break;
					}
				}
			}
			
			//update
			if (i + 1 == instructions.size())
				i = -1;
		}
		std::cout << steps;
	}


	//..............................

	void part2() {
		auto file = InputSetup::getFile("input8.txt");
		//read instructions
		std::string line;
		std::unordered_map<int, bool> instructions;
		getline(file, line);
		for (int i{ 0 }; i < line.size(); i++) {
			if (line[i] == 'L')
				instructions[i] = true;
			else
				instructions[i] = false;
		}

		//read map
		struct Direction {
			std::unordered_map<std::string, Direction>::iterator left;
			std::unordered_map<std::string, Direction>::iterator right;
		};
		std::unordered_map<std::string, Direction> map;
		getline(file, line);
		while (getline(file, line)) {
			map[line.substr(0, 3)];
		}
		file.close(); file.open("input8.txt");
		getline(file, line); getline(file, line);
		while (getline(file, line)) {
			map[line.substr(0, 3)] = Direction{ map.find(line.substr(7,3)), map.find(line.substr(12,3)) };
		}


		//count steps
		int steps{ 0 };
		std::unordered_map<std::string, Direction>::iterator node;
		std::list < int > nodes;
		//determin start nodes
		for (const auto& x : map) {
			if (x.first[2] == 'A') {
				node = map.find(x.first);
				steps = 0; int i = 0;
				while (true) {
					steps++;
					if (instructions[i] == true) {
						node = node->second.left;
					}
					else {
						node = node->second.right;
					}

					//abbruch bedingung
					if (node->first[2] == 'Z') break;

					//update
					if (++i == instructions.size()) {
						//std::cout << steps << '\n';
						i = 0;
					}
				}

				nodes.push_back(steps);
			}
			
		}
		
		int ar[6], i{0};
		nodes.sort();		
		for (const auto& x : nodes) {
			ar[i] = x;
			i++;
		}

		long long k{ 0 };
		bool isNotFinished = true;
		while (isNotFinished) {
			k++;
			//std::cout << k << '\n';
			isNotFinished = false;
			for (int i = 4; i >= 0; i--) {
				if ((k * ar[5]) % ar[i] != 0) {
					isNotFinished = true;
					break;
				}
		
			}
			
		}

		std::cout << k * ar[5];
	}

}
