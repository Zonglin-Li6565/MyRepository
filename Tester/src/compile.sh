#!/bin/bash
g++ -c ./Matrix/List/linkedlist.cpp ./Matrix/Dimension/dimension.h ./Matrix/Dimension/dimension.cpp ./Matrix/matrix.h ./Matrix/matrix.cpp forwardnode.h forwardnode.cpp memorycell.h memorycell.cpp Tester.cpp -std=c++11
g++ dimension.o forwardnode.o linkedlist.o matrix.o memorycell.o Tester.o -o Tester
rm dimension.o forwardnode.o linkedlist.o matrix.o memorycell.o Tester.o