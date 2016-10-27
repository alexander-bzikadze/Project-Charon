#include <iostream>
#include "lane.hpp"

void Lane::update_car(size_t road_length, size_t const recommended_speed, size_t const safe_distance, size_t const index)
{
	if (cars.size() == 0)
	{
		return;
	}
	if (index == 0)
	{
	coordinates[0] += cars[0].update(road_length - coordinates[0], 0, 1, 
					recommended_speed, safe_distance);
	}
	else
	{
		coordinates[index] += cars[index].update(coordinates[index - 1] - coordinates[index]
							- cars[index - 1].get_size(), cars[index - 1].get_speed(), 1,
							recommended_speed, safe_distance);
	}
}

std::vector<Car> const& Lane::get_cars() const
{
	return cars;
}

std::vector<size_t> const& Lane::get_coordinates() const
{
	return coordinates;
}

void Lane::add_car(Car const &car, size_t coordinate)
{
	cars.push_back(car);
	coordinates.push_back(coordinate);
}