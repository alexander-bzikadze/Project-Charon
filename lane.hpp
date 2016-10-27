#pragma once

#include <vector>
#include <string>

#include "car.hpp"

class Lane
{
public:
	Lane() = default;

	Lane(int road_length) :
		road_length(road_length) 
		{}

	void update(int const recommended_speed, int const safe_distance);
	void print() const;

	std::vector<Car> const& get_cars() const;
	std::vector<int> const& get_coordinates() const;

	void add_car(Car const &car, int coordinate);

private:
	std::vector<Car> cars;
	std::vector<int> coordinates;

	int road_length;
	std::string name;
};