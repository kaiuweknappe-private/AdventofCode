#include <iostream>
#include <fstream>
#include <string>
#include "InputSetup.h"

namespace D02{

	void part1() {
		auto file = InputSetup::getFile("input2.txt");
		std::string line, sets, cubes;
		int gameNum(0), sumOfSuccesfullGames(0);
		size_t firstPos(0), nextPos(0);
		size_t firstPos2(0), nextPos2(0);
		bool isPossible;

		while (getline(file, line))
		{
			gameNum++;
			isPossible = true;
			line.erase(0, line.find(':') + 2);
			firstPos = nextPos = 0;
			while (nextPos != std::string::npos)
			{
				nextPos = line.find(';', firstPos + 1);
				sets = line.substr(firstPos, nextPos-firstPos);
				firstPos = nextPos+2;

				firstPos2 = nextPos2 = 0;
				while (nextPos2 != std::string::npos)
				{
					nextPos2 = sets.find(',', firstPos2 );
					cubes = sets.substr(firstPos2, nextPos2 - firstPos2);
					firstPos2 = nextPos2 + 2;

					//einzelne cubes pruefen:
					if (cubes.find("red") != std::string::npos) {
						if (stoi(cubes) > 12)
							isPossible = false;
					}else if (cubes.find("blue") != std::string::npos) {
						if (stoi(cubes) > 14)
							isPossible = false;
					}else if (cubes.find("green") != std::string::npos) {
						if (stoi(cubes) > 13)
							isPossible = false;
					}

				}
				
				if (!isPossible)
					break;

			}

			if (isPossible)
				sumOfSuccesfullGames += gameNum;

		}

		std::cout << sumOfSuccesfullGames << std::endl;
	
	}

	void part2() {
		auto file = InputSetup::getFile("input2.txt");
		std::string line, sets, cubes;
		int power(0), sumPower(0), redMax, blueMax, greenMax;
		size_t firstPos(0), nextPos(0);
		size_t firstPos2(0), nextPos2(0);
		

		while (getline(file, line))
		{
			power = 0;
			redMax = blueMax = greenMax = 0;
			line.erase(0, line.find(':') + 2);
			firstPos = nextPos = 0;
			while (nextPos != std::string::npos)
			{
				nextPos = line.find(';', firstPos + 1);
				sets = line.substr(firstPos, nextPos - firstPos);
				firstPos = nextPos + 2;

				firstPos2 = nextPos2 = 0;
				while (nextPos2 != std::string::npos)
				{
					nextPos2 = sets.find(',', firstPos2);
					cubes = sets.substr(firstPos2, nextPos2 - firstPos2);
					firstPos2 = nextPos2 + 2;

					//einzelne cubes pruefen:
					if (cubes.find("red") != std::string::npos) {
						if (stoi(cubes) > redMax)
							redMax = stoi(cubes);
					}
					else if (cubes.find("blue") != std::string::npos) {
						if (stoi(cubes) > blueMax)
							blueMax = stoi(cubes);
					}
					else if (cubes.find("green") != std::string::npos) {
						if (stoi(cubes) > greenMax)
							greenMax = stoi(cubes);
					}

				}

			}

			//end of agame
			power = redMax * blueMax * greenMax;
			sumPower += power;
			
		}

		std::cout << sumPower << std::endl;
	}

}