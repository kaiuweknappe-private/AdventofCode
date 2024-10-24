#include <iostream>
#include <fstream>
#include <string>
#include "InputSetup.h"
#include <unordered_map>


namespace D07 {

	int getStrength(std::string& hand) {
		std::vector<int> diffCards;
		int temp;
		for (size_t i = 0; i < 5; i++) {
			temp = 0;

			for (size_t x = 0; x < 5; x++) {
				if (hand[x] == hand[i]) {
					if (x < i)
						break;
					temp++;
				}
			}

			if (temp != 0)
				diffCards.push_back(temp);
		}

		// return 1 (weakest).. 7 (strongest) 
		if (diffCards.size() == 5) {
			return 1; //high card
		}
		else if (diffCards.size() == 4) {
			return 2; //one pair
		}
		else if (diffCards.size() == 3) {
			for (const auto& card : diffCards) {
				if (card > 2) {
					return 4; // three of a kind
				}
			}
			return 3; //two pairs
		}
		else if (diffCards.size() == 2) {
			for (const auto& card : diffCards) {
				if (card > 3) {
					return 6; // four of a kind
				}
			}
			return 5; //full house
		}
		else if (diffCards.size() == 1) {
			return 7; // five of a kind
		}
	}

	struct Game {
		std::string hand;
		int bid;
		int type;
	};

	std::unordered_map<char, int> value;
	bool sortStrength(const Game& game1, const Game& game2) {
		if (game1.type < game2.type)
			return true;
		else if (game1.type > game2.type)
			return false;
		else { // type tie -> single card evaluation 
			for (size_t i = 0; i < 5; i++) {
				if (value[game1.hand[i]] < value[game2.hand[i]])
					return true;
				else if (value[game1.hand[i]] > value[game2.hand[i]])
					return false;
			}
		}
	}

	void part1() {
		auto file = InputSetup::getFile("test.txt");

		value['A'] = 13;
		value['K'] = 12;
		value['Q'] = 11;
		value['J'] = 10;
		value['T'] = 9;
		value['9'] = 8;
		value['8'] = 7;
		value['7'] = 6;
		value['6'] = 5;
		value['5'] = 4;
		value['4'] = 3;
		value['3'] = 2;
		value['2'] = 1;
		
		std::list <Game> games;
		std::string line, hand;
		int bid;
		while (getline(file, line)) {
			hand = line.substr(0, 5);
			bid = stoi(line.substr(5, std::string::npos));
			games.push_back(Game{ hand, bid, getStrength(hand) });
		}

		games.sort(sortStrength);

		int solution{ 0 }, it{ 0 };
		for (const auto& element : games) {
			it++;
			solution += it * element.bid;
		}

		std::cout << solution;
	}

	std::unordered_map<char, int> value2;
	bool sortStrength2(const Game& game1, const Game& game2) {
		if (game1.type < game2.type)
			return true;
		else if (game1.type > game2.type)
			return false;
		else { // type tie -> single card evaluation 
			for (size_t i = 0; i < 5; i++) {
				if (value2[game1.hand[i]] < value2[game2.hand[i]])
					return true;
				else if (value2[game1.hand[i]] > value2[game2.hand[i]])
					return false;
			}
		}
	}
	int getStrength2(std::string& hand) {
		std::unordered_map<char, int> diffCards;
		int temp, numJ{ 0 };
		char key;
		for (size_t i = 0; i < 5; i++) {
			temp = 0;
			key = hand[i];
			if (key == 'J')
				numJ++;

			for (size_t x = 0; x < 5; x++) {
				if (hand[x] == key) {
					if (x < i)
						break;
					temp++;
				}
			}

			if (temp != 0)
				diffCards[key] = (temp);
		}
		
		if (numJ > 0 && numJ < 5) {
			//higest card without J
			int mvpCard{ 0 };
			for (const auto& card : diffCards) {
				if (card.second > mvpCard && card.first != 'J')
					mvpCard = card.second;
			}
			//erase Js
			for (auto it = diffCards.begin(); it != diffCards.end(); it++) {
				if (it->first == 'J') {
					diffCards.erase(it);
					break;
				}
			}
			//add J cards to that stack
			for (auto& card : diffCards) {
				if (card.second == mvpCard) {
					card.second += numJ;
					break;
				}
			}
		}
		//debug
		/*std::cout << hand << "-> ";
		for (const auto& x : diffCards) {
			std::cout << x.second << "'" << x.first << "' , ";
		}
		std::cout << "\n";*/
		// debug
		
		// return 1 (weakest).. 7 (strongest) 
		if (diffCards.size() == 5) {
			return 1; //high card
		}
		else if (diffCards.size() == 4) {
			return 2; //one pair
		}
		else if (diffCards.size() == 3) {
			for (const auto& card : diffCards) {
				if (card.second > 2) {
					return 4; // three of a kind
				}
			}
			return 3; //two pairs
		}
		else if (diffCards.size() == 2) {
			for (const auto& card : diffCards) {
				if (card.second > 3) {
					return 6; // four of a kind
				}
			}
			return 5; //full house
		}
		else if (diffCards.size() == 1) {
			return 7; // five of a kind
		}
	}

	void part2() {
		auto file = InputSetup::getFile("input7.txt");


		value2['A'] = 13;
		value2['K'] = 12;
		value2['Q'] = 11;
		value2['T'] = 10;
		value2['9'] = 9;
		value2['8'] = 8;
		value2['7'] = 7;
		value2['6'] = 6;
		value2['5'] = 5;
		value2['4'] = 4;
		value2['3'] = 3;
		value2['2'] = 2;
		value2['J'] = 1;

		std::list <Game> games;
		std::string line, hand;
		int bid;
		while (getline(file, line)) {
			hand = line.substr(0, 5);
			bid = stoi(line.substr(5, std::string::npos));
			games.push_back(Game{ hand, bid, getStrength2(hand) });
		}

		games.sort(sortStrength2);
						
		int solution{ 0 }, it{ 0 };
		for (const auto& element : games) {
			it++;
			solution += it * element.bid;
			//std::cout << element.hand << "*" << element.type << '\n';
		}

		std::cout << solution;
	}

}
