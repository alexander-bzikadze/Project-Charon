all:
	g++ main.cpp side.cpp lane.cpp car.cpp -o main -std=c++11 -Wall
	./main