#include <iostream>

#include "one_lane_side.hpp"

void One_lane_side::update()
{
	lane.update(recommended_speed, safe_distance);
}

void One_lane_side::print() const
{
	auto coordinates = lane.get_coordinates();
	for (size_t i = 0; i < coordinates.size(); ++i)
	{
		std::cout << coordinates[i] << std::endl;
	}
	std::cout << std::endl;
}

void One_lane_side::add_to_lane(Car const& car, size_t lane_number = 0)
{
	lane.add_car(car, 0);
}