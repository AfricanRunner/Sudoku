
#include "index_list.h"

#include <cstdlib>
#include <ctime>

using namespace sdk;

index_list::index_list(int dim): dim(dim)
{
	srand(time(NULL));
	values = new int*[dim * dim];
	index = new int[dim * dim];
	for (int i = 0; i < dim * dim; i++)
	{
		index[i] = i;
		values[i] = new int[dim];
		for (int j = 0; j < dim; j++)
			values[i][j] = j + 1;
	}
}

index_list::~index_list()
{
	for (int i = 0; i < dim * dim; i++)
		delete [] values[i];
	delete [] values;
	delete [] index;
}

void c_shuffle(int* list, int len)
{
	for (int i = len - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		int t = list[i];
		list[i] = list[j];
		list[j] = t;
	}
}

void index_list::shuffle()
{
	c_shuffle(index, dim * dim);
	for (int i = 0; i < dim * dim; i++)
		c_shuffle(values[i], dim);
}
