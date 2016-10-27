all:
	g++ main.cpp one_lane_side.cpp lane.cpp car.cpp -o main -std=c++11 -Wall
	./main