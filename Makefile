CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

main: main.o sudoku.o implication.o index_list.o stopwatch/stopwatch.o 
		$(CXX) $(CXXFLAGS) -o main main.o sudoku.o implication.o index_list.o stopwatch/stopwatch.o

main.o: main.cpp sudoku.h
		$(CXX) $(CXXFLAGS) -c main.cpp

sudoku.o: sudoku.cpp sudoku.h implication.h index_list.h

implication.o: implication.cpp implication.h sudoku.h

index_list.o: index_list.cpp index_list.h

stopwatch/stopwatch.o: stopwatch/stopwatch.h

