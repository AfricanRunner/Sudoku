
#ifndef INDEX_LIST_H
#define INDEX_LIST_H

namespace sdk
{
	struct index_list
	{
	private:
		int dim;
		int* index;
		int** values;

	public:
		index_list(int dim);
		~index_list();

		void shuffle();

		int get_index(int i) { return index[i]; }
		int get_value(int i, int j) { return values[i][j]; }
	};
};

#endif /* INDEX_LIST_H */
