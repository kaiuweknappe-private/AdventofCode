#include <iostream>
#include <fstream>
#include <string>
#include "InputSetup.h"
#include <list>
#include <vector>
#include <cmath>
#define ll long long

namespace D11 {

	void part1() {
		auto file = InputSetup::getFile("input11.txt");
		std::list<std::string> map;
		std::string line;
		while (getline(file, line)) {
			map.emplace_back(line);
			if (line.find('#') == std::string::npos) //row expansion
				map.emplace_back(line);
		}
		//coulum expansion
		bool isGalaxy;
		int rowlength{ (int) map.begin()->size() };
		for (int i = 0; i < rowlength; i++) {
			isGalaxy = false;
			for (auto it = map.begin(); it != map.end(); it++) {
				if (it->at(i) == '#')
					isGalaxy = true;
			}
			if (!isGalaxy) {
				i++;
				rowlength++;
				for (auto it = map.begin(); it != map.end(); it++) {
					it->insert(i, ".");
				}
			}
		}
		//debug
		/*for (auto it = map.begin(); it != map.end(); it++) {
			std::cout << *it << '\n';
		}*/

		//map all galaxies
		struct Pos { int y; int x; };
		std::vector<Pos> galaxies;
		int y{ 0 };
		for (auto it = map.begin(); it != map.end(); y++, it++) {
			if (it->find('#') != std::string::npos) {
				for (int x = 0; x < rowlength; x++) {
					if (it->at(x) == '#') {
						galaxies.push_back({y, x});
					}
				}
			}
		}

		//calculate pathlength for each pair
		int sum{ 0 }, currentlength;
		for (auto it = galaxies.begin(); it != galaxies.end(); it++) {
			for (auto itr = std::next(it); itr != galaxies.end(); itr++) {
				if (it == itr) continue;
				//each pair with it and itr
				currentlength = 0;
				currentlength += std::abs(it->y - itr->y);
				currentlength += std::abs(it->x - itr->x);
				sum += currentlength;
			}
		}

		std::cout << sum;
	}

	void part2() {
		auto file = InputSetup::getFile("input11.txt"); 
		struct Pos { ll y; ll x; };
		std::vector<Pos> galaxies;
		std::string line;
		std::list<std::string> map;
		for (ll currentY{ 0 }; getline(file, line); currentY++) {
			map.push_back(line);
			if (line.find('#') == std::string::npos) { // row expansion
				currentY += 999999;          ////////////////////////////
				continue;
			}
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == '#') {
					galaxies.push_back(Pos{ currentY, i });
				}
			}
			
		}
		//coulum expansion
		ll delta{ 0 };
		for (size_t i = 0; i < map.begin()->size(); i++) {
			bool isGalaxy{ false };
			for (auto it = map.begin(); it != map.end(); it++) {
				if (it->at(i) == '#') {
					isGalaxy = true;
					break;
				}
			}
			if (!isGalaxy) {
				//edit galaxies
				for (auto& galax : galaxies) {
					if (galax.x > i + delta)      
						galax.x += 999999;          ///////////////////////////
				}
				delta += 999999;          ///////////////////////////
			}
		}
		////debug
		//for (const auto& gal : galaxies) {
		//	std::cout << gal.y << " |" << gal.x << '\n';
		//}

		//calculate pathlength for each pair
		ll sum{ 0 }, currentlength;
		for (auto it = galaxies.begin(); it != galaxies.end(); it++) {
			for (auto itr = std::next(it); itr != galaxies.end(); itr++) {
				if (it == itr) continue;
				//each pair with it and itr
				currentlength = 0;
				currentlength += std::abs(it->y - itr->y);
				currentlength += std::abs(it->x - itr->x);
				sum += currentlength;
			}
		}

		std::cout << sum;
	}

}
