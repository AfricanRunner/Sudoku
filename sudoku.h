
#ifndef SUDOKU_H
#define SUDOKU_H

#include <cstdint>
#include <vector>
#include <string>

namespace sdk
{
	struct implication;

	struct sudoku
	{
		friend implication;

	private:
		int dim;
		int v_sec;
		int h_sec;

		uint64_t* row_map;
		uint64_t* col_map;
		uint64_t* blk_map;

		int* grid;

		int size() const { return dim * dim; }

		int get_row(int i) const { return i / dim; }
		int get_col(int i) const { return i % dim; }
		int get_blk(int r, int c) const { return r / v_sec * h_sec + c / h_sec; }

		int get(int i) const { return grid[i]; }
		int get(int r, int c) const { return grid[r * dim + c]; }

		static uint64_t map(int v) { return v ? UINT64_C(1) << (v - 1) : UINT64_C(0); };

		void set(int i, int v) 
		{
			uint64_t mi = map(grid[i]);
			uint64_t mf = map(v);
			int r = get_row(i);
			int c = get_col(i);

			row_map[r] ^= mi;
			col_map[c] ^= mi;
			blk_map[get_blk(r, c)] ^= mi;

			row_map[r] |= mf;
			col_map[c] |= mf;
			blk_map[get_blk(r, c)] |= mf;

			grid[i] = v;
		}

		bool can_set(int i, int v) const
		{
			uint64_t m = map(v);
			int r = get_row(i);
			int c = get_col(i);

			return !((row_map[r] & m) ||
					 (col_map[c] & m) || 
					 (blk_map[get_blk(r, c)] & m));
		}

		bool valid_rows() const;
		bool valid_cols() const;
		bool valid_blks() const;

		void solve(int pos, bool keep_changes, int& n_solutions);

	public:
		sudoku(int dim);
		sudoku(const std::vector<int> in);
		~sudoku();

		bool solve();
		bool valid() const;

		std::string str() const;
	};
};

#endif /* SUDOKU_H */
