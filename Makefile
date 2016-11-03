all:
	g++ main.cpp cross_road.cpp traffic_light.cpp side.cpp lane.cpp car.cpp -o main -std=c++11 -Wall
	./main