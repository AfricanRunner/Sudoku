#include <iostream>

#include "sudoku.h"

#include "stopwatch/stopwatch.h"

using namespace sdk;

int main()
{
	std::vector<int> x16 = {1, 0, 0, 2, 3, 4, 0, 0, 12, 0, 6, 0, 0, 0, 7, 0,
							0, 0, 8, 0, 0, 0, 7, 0, 0, 3, 0, 0, 9, 10, 6, 11,
							0, 12, 0, 0, 10, 0, 0, 1, 0, 13, 0, 11, 0, 0, 14, 0,
							3, 0, 0, 15, 2, 0, 0, 14, 0, 0, 0, 9, 0, 0, 12, 0,
							13, 0, 0, 0, 8, 0, 0, 10, 0, 12, 2, 0, 1, 15, 0, 0,
							0, 11, 7, 6, 0, 0, 0, 16, 0, 0, 0, 15, 0, 0, 5, 13,
							0, 0, 0, 10, 0, 5, 15, 0, 0, 4, 0, 8, 0, 0, 11, 0,
							16, 0, 0, 5, 9, 12, 0, 0, 1, 0, 0, 0, 0, 0, 8, 0,
							0, 2, 0, 0, 0, 0, 0, 13, 0, 0, 12, 5, 8, 0, 0, 3,
							0, 13, 0, 0, 15, 0, 3, 0, 0, 14, 8, 0, 16, 0, 0, 0,
							5, 8, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 13, 9, 15, 0,
							0, 0, 12, 4, 0, 6, 16, 0, 13, 0, 0, 7, 0, 0, 0, 5,
							0, 3, 0, 0, 12, 0, 0, 0, 6, 0, 0, 4, 11, 0, 0, 16,
							0, 7, 0, 0, 16, 0, 5, 0, 14, 0, 0, 1, 0, 0, 2, 0,
							11, 1, 15, 9, 0, 0, 13, 0, 0, 2, 0, 0, 0, 14, 0, 0,
							0, 14, 0, 0, 0, 11, 0, 2, 0, 0, 13, 3, 5, 0, 0, 12};
	
//	std::vector<int> in = {5, 3, 0, 0, 7, 0, 0, 0, 0,
//						   6, 0, 0, 1, 9, 5, 0, 0, 0,
//						   0, 9, 8, 0, 0, 0, 0, 6, 0,
//						   8, 0, 0, 0, 6, 0, 0, 0, 3,
//						   4, 0, 0, 8, 0, 3, 0, 0, 1,
//						   7, 0, 0, 0, 2, 0, 0, 0, 6,
//						   0, 6, 0, 0, 0, 0, 2, 8, 0,
//						   0, 0, 0, 4, 1, 9, 0, 0, 5,
//						   0, 0, 0, 0, 8, 0, 0, 7, 9};
	
	std::vector<int> in = {0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 3, 0, 8, 5,
						   0, 0, 1, 0, 2, 0, 0, 0, 0,
						   0, 0, 0, 5, 0, 7, 0, 0, 0,
						   0, 0, 4, 0, 0, 0, 1, 0, 0,
						   0, 9, 0, 0, 0, 0, 0, 0, 0,
						   5, 0, 0, 0, 0, 0, 0, 7, 3,
						   0, 0, 2, 0, 1, 0, 0, 0, 0,
						   0, 0, 0, 0, 4, 0, 0, 0, 9};

	sudoku s = in;
	//sudoku s = x16;

	std::cout << s.str() << std::endl;
	std::cout << (s.valid() ? "Valid!" : "Invalid :(") << std::endl;

	sw::stopwatch sw;
	std::cout << "Solving sudoku..." << std::endl;
	sw.start();

	std::cout << (s.solve() ? "Solved!" : "Failed :(") << std::endl;

	sw.stop();
	std::cout << "Finished in " << sw.total_str() << std::endl;

	std::cout << s.str() << std::endl;
	std::cout << (s.valid() ? "Valid!" : "Invalid :(") << std::endl;
	
	//sudoku s = sudoku::generate(9);

	//std::cout << s.str() << std::endl;

	return 0;
}