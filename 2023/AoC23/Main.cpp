#include <iostream>
#include "DefPuzzels.h"
#include <chrono>

int main() {
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

	//Part-solution:
	D08::part1();
	
	std::chrono::high_resolution_clock::time_point ende = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration diff = ende - start;
	double laufzeit = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
	std::cout << "\n\nLaufzeit: " << laufzeit << " ms";

	return 0;
}