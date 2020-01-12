
#ifndef IMPLICATION_H
#define IMPLICATION_H

namespace sdk
{
	struct sudoku;

	struct implication
	{
	private:
		int size;
		int* grid;
	
	public:
		implication(int size);
		~implication();

		bool make(sudoku& sdk);
		void undo(sudoku& sdk) const;
	};
};

#endif /* IMPLICATION_H */
