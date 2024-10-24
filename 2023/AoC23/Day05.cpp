#include <iostream>
#include <fstream>
#include <string>
#include "InputSetup.h"
#include <unordered_map>
#include <vector>
#include <map>


namespace D05 {

	void part1() {
		auto file = InputSetup::getFile("input5.txt");
		std::string line;
		struct rangePart {
			long long partRangeStart;
			long long length;
			long long delta;
		};

		//phrase seeds
		std::vector<long long> values;
		getline(file, line);
		size_t nextSeedStart = line.find(" ");
		while (nextSeedStart != std::string::npos) {
			values.push_back(stoll(line.substr(nextSeedStart, std::string::npos)));
			nextSeedStart = line.find(' ', nextSeedStart+1);
			//std::cout << nextSeedStart << " ";
		}

		//for (const auto& x : values)
		//	std::cout << x << '\n';

		//phrase ranges
		std::vector < rangePart > ranges[7];
		int rangeNum{ -1 };
		long long length, inputStart, outputStart, delta;
		while (getline(file, line))	{
			if (line == "")
				continue;
			//check if new
			if (!std::isdigit(line[0])) {
				rangeNum++;
				continue;
			}
			
			//new part-range
			//read current line
			outputStart = stoll(line);
			nextSeedStart = line.find(' ');
			inputStart = stoll(line.substr(nextSeedStart, std::string::npos));
			length = stoll(line.substr(line.find(' ', nextSeedStart + 1), std::string::npos));
			delta = outputStart - inputStart;

			//add to range
			//std::cout << inputStart << " " << outputStart << " : " << delta << '\n';
			ranges[rangeNum].push_back(rangePart{ inputStart, length, delta });
		}

		//translate seeds to locations using the ranges
		for (rangeNum = 0; rangeNum < 7; rangeNum++) {
			for (auto& val : values) {
				for (const auto& r : ranges[rangeNum]) {
					if (val >= r.partRangeStart && val < r.partRangeStart + r.length) {
						val += r.delta;
						break;
					}
				}
	
			}
		}

		
		//cout the smalles location
		long long smallest = LLONG_MAX;
		for (const auto& x : values) {
			std::cout << x << " ";
			if (x < smallest) {
				smallest = x;
			}
		}
		std::cout << '\n' << smallest << '\n';

	}

	struct rangePart {
		long long partRangeStart;
		long long length;
		long long delta;
		long long end{ partRangeStart + length - 1 };
	};


	void part2() {
		auto file = InputSetup::getFile("input5.txt");
		std::string line;

		//phrase seeds
		std::vector<std::pair< long long, long long > > inValues, outValues;
		long long tempfirst, templength;
		getline(file, line);
		size_t nextSeedStart = line.find(" ");
		while (nextSeedStart != std::string::npos) {
			tempfirst = stoll(line.substr(nextSeedStart, std::string::npos));
			nextSeedStart = line.find(' ', nextSeedStart + 1);
			templength = stoll(line.substr(nextSeedStart, std::string::npos));
			inValues.push_back({ tempfirst, tempfirst + templength - 1 });
			nextSeedStart = line.find(' ', nextSeedStart + 1);
		}

		//phrase ranges
		std::map < long long, rangePart > ranges[7];
		int rangeNum{ -1 };
		long long length, inputStart, outputStart, delta;
		while (getline(file, line)) {
			if (line == "")
				continue;
			//check if new
			if (!std::isdigit(line[0])) {
				rangeNum++;
				continue;
			}

			//new part-range
			//read current line
			outputStart = stoll(line);
			nextSeedStart = line.find(' ');
			inputStart = stoll(line.substr(nextSeedStart, std::string::npos));
			length = stoll(line.substr(line.find(' ', nextSeedStart + 1), std::string::npos));
			delta = outputStart - inputStart;

			//add to range
			ranges[rangeNum][inputStart] = rangePart{ inputStart, length, delta };
		}

		//sortet map 
		std::map < size_t, rangePart > sRanges[7];

		for (size_t rangeNum = 0; rangeNum < 7; rangeNum++) { //every range
			int x = 0;
			for (auto it = ranges[rangeNum].begin(); it != ranges[rangeNum].end(); x++, it++) { //every rangepart 
				sRanges[rangeNum][x] = ranges[rangeNum][it->first];
			}
		}

		//determin outValues
		bool exit;
		for (size_t rangeNum = 0; rangeNum < 7; rangeNum++) {
			//inValues -> outValues
			for (const auto& rangePart : inValues) { //translate every input range

				//determin anchor
				size_t anchor{ sRanges[rangeNum].size() - 1 };
				for (const auto& range : sRanges[rangeNum]) {
					if (rangePart.first < range.second.partRangeStart) {
						anchor = range.first - 1;
						break;
					}
				}

				long long start{ rangePart.first }, end;
				exit = false;

				//anchor outof bounce front
				if (anchor == -1) {
					anchor++;
					start = sRanges[rangeNum][anchor].partRangeStart;

					if (rangePart.second < start) {
						outValues.push_back(std::make_pair(rangePart.first, rangePart.second));
						exit = true;
					}
					else {
						outValues.push_back(std::make_pair(rangePart.first, start - 1));
					}

				}

		
				while (!exit ) {
				
					long long& currentDelta{ sRanges[rangeNum][anchor].delta };
					end = sRanges[rangeNum][anchor].end;
					//4 verschiedene cases handeln
					if (start <= sRanges[rangeNum][anchor].end) {
						
						if (rangePart.second <= sRanges[rangeNum][anchor].end) { //case 1, complete in range
							outValues.push_back(std::make_pair(start + currentDelta, rangePart.second + currentDelta));
							exit = true;
						} else { //case 2, first overlap
							outValues.push_back(std::make_pair(start + currentDelta, end + currentDelta));
						}
						start = end + 1;
					}

					if (exit) break;
					anchor++;
					if (anchor >= sRanges[rangeNum].size()) break;

					//only if there is a gap to the next range part
					if (sRanges[rangeNum][anchor - 1].end == sRanges[rangeNum][anchor].partRangeStart - 1)  
						continue;
					end = sRanges[rangeNum][anchor].partRangeStart - 1;
					currentDelta = 0;
					if (rangePart.second < sRanges[rangeNum][anchor].partRangeStart) { //case 3
						outValues.push_back(std::make_pair(start + currentDelta, rangePart.second + currentDelta));
						exit = true;
					}
					else { //case 4
						outValues.push_back(std::make_pair(start + currentDelta, end + currentDelta));
					}
					//
					start = sRanges[rangeNum][anchor].partRangeStart;
				}

				if (!exit) {
					if (start == sRanges[rangeNum][anchor - 1].end + 1)
						outValues.push_back(std::make_pair(start, rangePart.second));
					else
						outValues.push_back(std::make_pair(rangePart.first, rangePart.second));
				}
			}
	
			//end of each range
			/*for (const auto& x : outValues) {
				std::cout << x.first << " : " << x.second << " / ";
			}
			std::cout << '\n';*/
			inValues = outValues;
			outValues.clear();
		}

		//find smallest
		long long smallest = LLONG_MAX;
		for (const auto& x : inValues) {
			if (x.first < smallest)
				smallest = x.first;
		}
		std::cout << smallest << '\n';
	}


}
