
#include "implication.h"
#include "sudoku.h"

#include <iostream>

using namespace sdk;

implication::implication(int size) : size(size)
{
	grid = new int[size];
	std::fill(grid, grid + size, 0);
}

implication::~implication()
{
	delete [] grid;
}

bool has_single_bit(uint64_t n)
{
	return !(n & (n - 1));
}

int pop_bit(uint64_t n)
{
	uint64_t i = UINT64_C(1);
	int pos = 1;
	while(!(i & n))
	{
		i = i << 1;
		pos++;
	}
	return pos;
}

void print_uint64_t(uint64_t n)
{
	for (int i = 0; i < 64; i++)
	{
		if(i % 4 == 0 && i != 0)
				std::cout << " ";
		std::cout << (n & (UINT64_C(1) << i) ? "1" : "0");
	}
	std::cout << std::endl;
}

bool implication::make(sudoku& sdk)
{
	bool made_change;
	do {
		made_change = false;
		for (int i = 0; i < size; i++) 
		{
			if(sdk.get(i) == 0)
			{
				int r = sdk.get_row(i);
				int c = sdk.get_col(i);
				uint64_t m = sudoku::map(sdk.dim + 1);

				uint64_t choices = ~(sdk.row_map[r] | sdk.col_map[c] |
									 sdk.blk_map[sdk.get_blk(r, c)]) & (m - 1);

				if(choices == 0)
				{
					return false;
				}
				else if(has_single_bit(choices))
				{
					sdk.set(i, pop_bit(choices));
					grid[i] = 1;
					made_change = true;
				}
			}
		}
	} while(made_change);

	return true;
}

void implication::undo(sudoku& sdk) const
{
	for (int i = 0; i < size; i++)
		if(grid[i])
			sdk.set(i, 0);
}
