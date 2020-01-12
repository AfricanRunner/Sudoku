
#include "sudoku.h"
#include "implication.h"

#include <cmath>
#include <sstream>
#include <iostream>

using namespace sdk;

int factor(int n)
{
	int previous = -1;
    int multiple = 1;
    int difference = n - 1;

    while(difference >= 0)
    {
        previous = multiple;
        do {
            multiple++;
        } while(n % multiple != 0);
        difference = n / multiple - multiple;
    }

    return previous;
}

bool sudoku::valid_rows() const
{
	for (int r = 0; r < dim; r++) 
	{
		uint64_t table = UINT64_C(0);
		uint64_t key;
		for (int c = 0; c < dim; c++) 
		{
			key = map(get(r, c));
			if(key & table)
				return false;
			else 
				table |= key;
		}
		if(table != row_map[r])
			return false;
	}
	return true;
}

bool sudoku::valid_cols() const
{
	for (int c = 0; c < dim; c++) 
	{
		uint64_t table = UINT64_C(0);
		uint64_t key;
		for (int r = 0; r < dim; r++) 
		{
			key = map(get(r, c));
			if(key & table)
				return false;
			else
				table |= key;
		}
		if(table != col_map[c])
			return false;
	}
	return true;
}

bool sudoku::valid_blks() const
{
	for (int r = 0; r < v_sec; r++) 
	{
		for (int c = 0; c < h_sec; c++) 
		{
			uint64_t table = UINT64_C(0);
			uint64_t key;
			for (int i = 0; i < v_sec; i++) 
			{
				for (int j = 0; j < h_sec; j++) 
				{
					key = map(get(r * v_sec + i, c * h_sec + j));
					if(key & table)
						return false;
					else
						table |= key;
				}
			}
			if(table != blk_map[r * h_sec + c])
				return false;
		}
	}
	return true;
}

void sudoku::solve(int pos, bool keep_changes, int& n_solutions)
{
	if(pos == size())
	{
		n_solutions--;
		return;
	}

	implication impl(size());
	
	if(!impl.make(*this))
	{
		impl.undo(*this);
		return;
	}

	while(grid[pos] != 0 && pos < size()) pos++;

	if(pos == size())
	{
		n_solutions--;
		if(!keep_changes)
			impl.undo(*this);
		return;
	}
	
	for (int i = 0; i < dim; i++)
	{
		if(can_set(pos, i + 1))
		{
			set(pos, i + 1);
			//solve(pos + 1, keep_changes, n_solutions);
			solve(pos + 1, keep_changes, n_solutions);
			if(n_solutions == 0)
			{
				if(!keep_changes)
					impl.undo(*this);
				return;
			}
		}
	}
	set(pos, 0);
	impl.undo(*this);
}

sudoku::sudoku(int dim) : dim(dim)
{
	v_sec = factor(dim);
	h_sec = dim / v_sec;
	
	row_map = new uint64_t[size()];
	col_map = new uint64_t[size()];
	blk_map = new uint64_t[size()];
	grid = new int[size()];

	std::fill(row_map, row_map + size(), UINT64_C(0));
	std::fill(col_map, col_map + size(), UINT64_C(0));
	std::fill(blk_map, blk_map + size(), UINT64_C(0));
	std::fill(grid, grid + size(), 0);
}

sudoku::sudoku(const std::vector<int> in) : sudoku(std::sqrt(in.size()))
{
	for (int i = 0; i < size(); i++)
		set(i, in[i]);
}

sudoku::~sudoku()
{
	delete [] row_map;
	delete [] col_map;
	delete [] blk_map;
	delete [] grid;
}

bool sudoku::solve()
{
	int a = 1;
	solve(0, true, a);
	return a == 0;
}

bool sudoku::valid() const
{
	return valid_rows() && valid_cols() && valid_blks();
}

std::string sudoku::str() const
{
	std::stringstream ss;
	for (int r = 0; r < dim; r++) 
	{
		if (r % v_sec == 0 && r != 0) 
		{
			for (int i = 0; i < dim + dim / h_sec - 1; i++)
				ss << "--";
			ss << "-\n";
		}
		for (int c = 0; c < dim; c++) 
		{
			if (c % h_sec == 0 && c != 0)
				ss << " |";
			ss << " " << get(r, c);
		}
		ss << "\n";
	}

	return ss.str();
}
