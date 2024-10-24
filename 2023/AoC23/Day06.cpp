#include <iostream>
#include <fstream>
#include <string>
#include "InputSetup.h"


namespace D06 {

	void part1() {
		//auto file = InputSetup::getFile("test.txt");
		//hardcoded i know...but fuck it with 8 numbers
		
		int time[] = { 61  ,   70  ,   90   ,  66 };
		int distance[] = { 643 ,  1184 ,  1362  , 1041 };
		int product{1}, currentDistance, moveTime, successes;
		for (size_t i = 0; i < 4; i++) {
			
			successes = 0;
			for (size_t charge = 0; charge <= distance[i]; charge++) {
				moveTime = time[i] - charge;
				currentDistance = moveTime * charge;

				if (currentDistance > distance[i]) {
					successes++;
				}
			}
			
			product *= successes;
		}

		std::cout << product << '\n';
	}

	void part2() {
		//auto file = InputSetup::getFile(".txt");
		long long time{ 61709066 };
		long long distance{ 643118413621041 };
		long long moveTime;
		int begin;
		
		
		for (size_t charge = 0; true; charge++) {
			moveTime = time - charge;

			if (moveTime * charge >= distance) {
				begin = charge;
				break;
			}
		}


		//std::cout << begin << '\n';
		begin *= 2;
		std::cout << time - begin + 1 << '\n';
	}

}
