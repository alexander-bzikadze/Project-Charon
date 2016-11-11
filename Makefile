all:
	g++ main.cpp standard_builder.cpp traffic_light.cpp cross_road.cpp side.cpp lane.cpp car.cpp -o main -std=c++11 -Wall
	./main