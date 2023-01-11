CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

main: main.o sudoku.o implication.o stopwatch/stopwatch.o
		$(CXX) $(CXXFLAGS) -o main main.o sudoku.o implication.o stopwatch/stopwatch.o

main.o: main.cpp sudoku.h
		$(CXX) $(CXXFLAGS) -c main.cpp

sudoku.o: sudoku.cpp sudoku.h implication.h

implication.o: implication.cpp implication.h sudoku.h

stopwatch/stopwatch.o: stopwatch/stopwatch.h

clean:
	find . -type f -name "*.o" | xargs -t rm
