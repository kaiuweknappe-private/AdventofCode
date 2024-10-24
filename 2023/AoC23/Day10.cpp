#include <iostream>
#include <fstream>
#include <string>
#include "InputSetup.h"
#include <unordered_map>
#include <map>
#include <algorithm>
#include <numeric>

namespace D10 {

	void part1() {
		auto file = InputSetup::getFile("input10.txt");

		struct Pos {
			int y;
			int x;
		}pos;
		//read input into 2d map
		std::unordered_map <int, std::unordered_map<int, char>> map;
		std::string line;
		for (int y = 0; getline(file, line); y++) {
			for (int x = 0; x < line.size(); x++) {
				map[y][x] = line[x];
				//std::cout << line[x];
				if (line[x] == 'S')
					pos = { y, x };
			}
		}


		int loopLength{ 1 }, direction;
		// determin first step manually ... also assuming S is not on the edge
		if (map[pos.y-1][pos.x] == '|' || map[pos.y - 1][pos.x] == '7' || map[pos.y - 1][pos.x] == 'F') { //north | 7 F
			pos.y--;
			direction = 1;
		}
		else if (map[pos.y][pos.x+1] == '-' || map[pos.y][pos.x+1] == 'J' || map[pos.y][pos.x + 1] == '7') { //east - J 7
			pos.x++;
			direction = 2;
		}
		else if (map[pos.y + 1][pos.x] == '|' || map[pos.y + 1][pos.x] == 'L' || map[pos.y +1][pos.x] == 'J') { //south | L J
			pos.y++;
			direction = 3;
		}

		while (map[pos.y][pos.x] != 'S') {
			loopLength++;
			//determin next Pos
			if (direction == 1) {
				if (map[pos.y][pos.x] == '|') {
					pos.y--;
				}
				else if (map[pos.y][pos.x] == 'F') {
					direction = 2;
					pos.x++;
				} 
				else if (map[pos.y][pos.x] == '7') {
					direction = 4;
					pos.x--;
				}
			} 
			else if (direction == 2) {
				if (map[pos.y][pos.x] == '-') {
					pos.x++;
				}
				else if (map[pos.y][pos.x] == 'J') {
					direction = 1;
					pos.y--;
				}
				else if (map[pos.y][pos.x] == '7') {
					direction = 3;
					pos.y++;
				}
			} 
			else if (direction == 3) {
				if (map[pos.y][pos.x] == '|') {
					pos.y++;
				}
				else if (map[pos.y][pos.x] == 'J') {
					direction = 4;
					pos.x--;
				}
				else if (map[pos.y][pos.x] == 'L') {
					direction = 2;
					pos.x++;
				}
			}
			else if (direction == 4) {
				if (map[pos.y][pos.x] == '-') {
					pos.x--;
				}
				else if (map[pos.y][pos.x] == 'L') {
					direction = 1;
					pos.y--;
				}
				else if (map[pos.y][pos.x] == 'F') {
					direction = 3;
					pos.y++;
				}
			}
		}
	
		std::cout << loopLength << ' ' << loopLength / 2; // +1 ?
	}

	void part2() {
		auto file = InputSetup::getFile("input10.txt");
		struct Pos {
			int y;
			int x;
		}pos;
		//read input into 2d map
		std::unordered_map <int, std::unordered_map<int, char>> map;
		std::string line;
		for (int y = 0; getline(file, line); y++) {
			for (int x = 0; x < line.size(); x++) {
				map[y][x] = line[x];
				if (line[x] == 'S')
					pos = { y, x };
			}
		}

		//std::cout << "S: " << pos.y << " | " << pos.x;
		std::map<int, std::list<int>> mainLoop, leftLoop, rightLoop;
		mainLoop[pos.y].push_back(pos.x); // adding S 
		int direction;
		// determin first step manually ... also assuming S is not on the edge
		if (map[pos.y - 1][pos.x] == '|' || map[pos.y - 1][pos.x] == '7' || map[pos.y - 1][pos.x] == 'F') { //north | 7 F
			pos.y--;
			direction = 1;
		}
		else if (map[pos.y][pos.x + 1] == '-' || map[pos.y][pos.x + 1] == 'J' || map[pos.y][pos.x + 1] == '7') { //east - J 7
			pos.x++;
			direction = 2;
		}
		else if (map[pos.y + 1][pos.x] == '|' || map[pos.y + 1][pos.x] == 'L' || map[pos.y + 1][pos.x] == 'J') { //south | L J
			pos.y++;
			direction = 3;
		}
		while (map[pos.y][pos.x] != 'S') {
			//save pipe pos
			mainLoop[pos.y].push_back(pos.x); 

			//determin next Pos
			if (direction == 1) {
				if (map[pos.y][pos.x] == '|') {
					leftLoop[pos.y].push_back(pos.x - 1);
					rightLoop[pos.y].push_back(pos.x + 1);
					pos.y--;
				}
				else if (map[pos.y][pos.x] == 'F') {
					leftLoop[pos.y].push_back(pos.x - 1);
					leftLoop[pos.y-1].push_back(pos.x - 1);
					leftLoop[pos.y-1].push_back(pos.x);
					rightLoop[pos.y + 1].push_back(pos.x + 1);
					direction = 2;
					pos.x++;
				}
				else if (map[pos.y][pos.x] == '7') {
					leftLoop[pos.y + 1].push_back(pos.x - 1);
					rightLoop[pos.y].push_back(pos.x + 1);
					rightLoop[pos.y - 1].push_back(pos.x);
					rightLoop[pos.y - 1].push_back(pos.x + 1);
					direction = 4;
					pos.x--;
				}
			}
			else if (direction == 2) {
				if (map[pos.y][pos.x] == '-') {
					leftLoop[pos.y - 1].push_back(pos.x);
					rightLoop[pos.y+1].push_back(pos.x);
					pos.x++;
				}
				else if (map[pos.y][pos.x] == 'J') {
					leftLoop[pos.y - 1].push_back(pos.x - 1);
					rightLoop[pos.y].push_back(pos.x + 1);
					rightLoop[pos.y +1].push_back(pos.x + 1);
					rightLoop[pos.y+1].push_back(pos.x);
					direction = 1;
					pos.y--;
				}
				else if (map[pos.y][pos.x] == '7') {
					leftLoop[pos.y - 1].push_back(pos.x);
					leftLoop[pos.y - 1].push_back(pos.x + 1);
					leftLoop[pos.y].push_back(pos.x + 1);
					rightLoop[pos.y +1].push_back(pos.x - 1);
					direction = 3;
					pos.y++;
				}
			}
			else if (direction == 3) {
				if (map[pos.y][pos.x] == '|') {
					leftLoop[pos.y].push_back(pos.x + 1);
					rightLoop[pos.y].push_back(pos.x - 1);
					pos.y++;
				}
				else if (map[pos.y][pos.x] == 'J') {
					leftLoop[pos.y].push_back(pos.x + 1);
					leftLoop[pos.y+1].push_back(pos.x + 1);
					leftLoop[pos.y+1].push_back(pos.x);
					rightLoop[pos.y - 1].push_back(pos.x - 1);
					direction = 4;
					pos.x--;
				}
				else if (map[pos.y][pos.x] == 'L') {
					leftLoop[pos.y - 1].push_back(pos.x + 1);
					rightLoop[pos.y].push_back(pos.x - 1);
					rightLoop[pos.y +1].push_back(pos.x - 1);
					rightLoop[pos.y+1].push_back(pos.x);
					direction = 2;
					pos.x++;
				}
			}
			else if (direction == 4) {
				if (map[pos.y][pos.x] == '-') {
					leftLoop[pos.y + 1].push_back(pos.x);
					rightLoop[pos.y-1].push_back(pos.x);
					pos.x--;
				}
				else if (map[pos.y][pos.x] == 'L') {
					leftLoop[pos.y +1].push_back(pos.x);
					leftLoop[pos.y + 1].push_back(pos.x - 1);
					leftLoop[pos.y].push_back(pos.x - 1);
					rightLoop[pos.y-1].push_back(pos.x + 1);
					direction = 1;
					pos.y--;
				}
				else if (map[pos.y][pos.x] == 'F') {
					leftLoop[pos.y + 1].push_back(pos.x + 1);
					rightLoop[pos.y-1].push_back(pos.x);
					rightLoop[pos.y-1].push_back(pos.x - 1);
					rightLoop[pos.y].push_back(pos.x - 1);
					direction = 3;
					pos.y++;
				}
			}
		}
	
		//debug
		int leftLooplength{ 0 };
		for (auto ity = leftLoop.begin(); ity != leftLoop.end(); ity++)
			leftLooplength += ity->second.size();
		int rightLooplength{ 0 };
		for (auto ity = rightLoop.begin(); ity != rightLoop.end(); ity++)
			rightLooplength += ity->second.size();
		std::cout << '\n' << leftLooplength << ' ' << rightLooplength;

		//left and right loop filtern.. remove: out of bounce, doppelt, Main loop member
		int ymax{(int) map.size() - 1 }, xmax{ (int) map[0].size() - 1 };
		for (auto ity = leftLoop.begin(); ity != leftLoop.end(); ity++) {
			//y out of bounce
			if (ity->first < 0 || ity->first > ymax) {
				ity = leftLoop.erase(ity);
				continue;
			}
			ity->second.sort();
			if (mainLoop.find(ity->first) != mainLoop.end())
				mainLoop[ity->first].sort();
			//x out of bounce and double
			for (auto itx = ity->second.begin(); itx != ity->second.end(); ) {
				if ( *itx < 0 || *itx > xmax) {
					itx = ity->second.erase(itx);
					continue;
				}
				if (mainLoop.find(ity->first) != mainLoop.end()) {//Main loop member
					if (std::binary_search(mainLoop[ity->first].begin(), mainLoop[ity->first].end(), *itx)) {
						itx = ity->second.erase(itx);
						continue;
					}
				}
				if (std::next(itx) != ity->second.end()) {
					if (*itx == *std::next(itx)) {
						itx = ity->second.erase(itx);
						continue;
					}
				}
				itx++;
			}
		}

		for (auto ity = rightLoop.begin(); ity != rightLoop.end(); ity++) {
			//y out of bounce
			if (ity->first < 0 || ity->first > ymax) {
				ity = rightLoop.erase(ity);
				continue;
			}
			ity->second.sort();
			if (mainLoop.find(ity->first) != mainLoop.end())
				mainLoop[ity->first].sort();
			//x out of bounce and double
			for (auto itx = ity->second.begin(); itx != ity->second.end(); ) {
				if (*itx < 0 || *itx > xmax) {
					itx = ity->second.erase(itx);
					continue;
				} 
				if (mainLoop.find(ity->first) != mainLoop.end()) { //main loop member
					if (std::binary_search(mainLoop[ity->first].begin(), mainLoop[ity->first].end(), *itx)) {
						itx = ity->second.erase(itx);
						continue;
					}
				}
				if (std::next(itx) != ity->second.end() && *itx == *std::next(itx)) { // doppelt
					itx = ity->second.erase(itx);
					continue;
				}
				itx++;
				
			}
		}

		//count length
		leftLooplength= 0 ;
		for (auto ity = leftLoop.begin(); ity != leftLoop.end(); ity++) 
			leftLooplength += ity->second.size();
		
		rightLooplength= 0;
		for (auto ity = rightLoop.begin(); ity != rightLoop.end(); ity++)
			rightLooplength += ity->second.size();
		std::cout << '\n' << leftLooplength << ' ' << rightLooplength;
		
		//add section cores to (right-)looplength ...tbd.. <- old plan doesnt work as intendet
		//i ended up counting the one hole manulee
		std::ofstream outfile("output10.txt");
		for (int y = 0; y <= ymax; y++) {
			std::string line{ "                                                                                                                                                                                                              " };
			for (auto it = rightLoop[y].begin(); it != rightLoop[y].end(); it++) {
				line.replace(*it, 1, "O");
			}
			outfile << line << '\n';
		}

		//if i would go for a cleaner solution i would try to recursivly repeat the inner loop find algorithm
		//till the new inner loop has 0 elements

	}
	
	void part2_2() {
		auto file = InputSetup::getFile("input10.txt");

		struct Pos {
			int y;
			int x;
		}pos;
		//read input into 2d map
		std::unordered_map <int, std::unordered_map<int, char>> map;
		std::string line;
		for (int y = 0; getline(file, line); y++) {
			for (int x = 0; x < line.size(); x++) {
				map[y][x] = line[x];
				//std::cout << line[x];
				if (line[x] == 'S')
					pos = { y, x };
			}
		}

		std::vector<Pos> integerPoints;
		integerPoints.push_back({ pos.y, pos.x });
		int loopLength{ 1 }, direction;
		// determin first step manually ... also assuming S is not on the edge
		if (map[pos.y - 1][pos.x] == '|' || map[pos.y - 1][pos.x] == '7' || map[pos.y - 1][pos.x] == 'F') { //north | 7 F
			pos.y--;
			direction = 1;
		}
		else if (map[pos.y][pos.x + 1] == '-' || map[pos.y][pos.x + 1] == 'J' || map[pos.y][pos.x + 1] == '7') { //east - J 7
			pos.x++;
			direction = 2;
		}
		else if (map[pos.y + 1][pos.x] == '|' || map[pos.y + 1][pos.x] == 'L' || map[pos.y + 1][pos.x] == 'J') { //south | L J
			pos.y++;
			direction = 3;
		}

		while (map[pos.y][pos.x] != 'S') {
			loopLength++;
			//determin next Pos
			if (direction == 1) {
				if (map[pos.y][pos.x] == '|') {
					pos.y--;
				}
				else if (map[pos.y][pos.x] == 'F') {
					integerPoints.push_back({ pos.y, pos.x });
					direction = 2;
					pos.x++;
				}
				else if (map[pos.y][pos.x] == '7') {
					integerPoints.push_back({ pos.y, pos.x });
					direction = 4;
					pos.x--;
				}
			}
			else if (direction == 2) {
				if (map[pos.y][pos.x] == '-') {
					pos.x++;
				}
				else if (map[pos.y][pos.x] == 'J') {
					integerPoints.push_back({ pos.y, pos.x });
					direction = 1;
					pos.y--;
				}
				else if (map[pos.y][pos.x] == '7') {
					integerPoints.push_back({ pos.y, pos.x });
					direction = 3;
					pos.y++;
				}
			}
			else if (direction == 3) {
				if (map[pos.y][pos.x] == '|') {
					pos.y++;
				}
				else if (map[pos.y][pos.x] == 'J') {
					integerPoints.push_back({ pos.y, pos.x });
					direction = 4;
					pos.x--;
				}
				else if (map[pos.y][pos.x] == 'L') {
					integerPoints.push_back({ pos.y, pos.x });
					direction = 2;
					pos.x++;
				}
			}
			else if (direction == 4) {
				if (map[pos.y][pos.x] == '-') {
					pos.x--;
				}
				else if (map[pos.y][pos.x] == 'L') {
					integerPoints.push_back({ pos.y, pos.x });
					direction = 1;
					pos.y--;
				}
				else if (map[pos.y][pos.x] == 'F') {
					integerPoints.push_back({ pos.y, pos.x });
					direction = 3;
					pos.y++;
				}
			}
		}

		//determin A with shoelace formula
		double A{ 0 } , temp;
		for (auto it = integerPoints.begin(); it != std::prev(integerPoints.end()); it++) {
			temp = 0;
			temp += (it)->x * std::next(it)->y;
			temp -= (it)->y * std::next(it)->x;
			A += temp;
		}
		temp = 0;
		temp += std::prev(integerPoints.end())->x * integerPoints.begin()->y;
		temp -= std::prev(integerPoints.end())->y * integerPoints.begin()->x;
		A += temp;
		A /= 2;

		std::cout << A;
		int& b = loopLength;
		std::cout << '\n' << b;

		// infirior points i with pick's thereom
		double i = A - (b / 2) + 1;
		std::cout << '\n' << i;
	}
}
