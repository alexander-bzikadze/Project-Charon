all:
	g++ main.cpp car_degenerator.cpp car_generator.cpp cross_road.cpp side.cpp lane.cpp car.cpp -o main -std=c++11 -Wall
	./main