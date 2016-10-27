#include <iostream>
#include "lane.hpp"

void Lane::update(int const recommended_speed, int const safe_distance)
{
	if (cars.size() == 0)
		return;
	coordinates[0] += cars[0].update(road_length - coordinates[0], 0, 1, 
					recommended_speed, safe_distance);
	for (size_t i = 1; i < cars.size(); ++i)
	{
		coordinates[i] += cars[i].update(coordinates[i - 1] - coordinates[i] - cars[i - 1].get_size(), cars[i - 1].get_speed(), 1,
											recommended_speed, safe_distance);
	}
}

void Lane::print() const
{
	for (size_t i = 0; i < coordinates.size(); ++i)
	{
		std::cout << coordinates[i] << std::endl;
	}
	std::cout << std::endl;
}

std::vector<Car> const& Lane::get_cars() const
{
	return cars;
}

std::vector<int> const& Lane::get_coordinates() const
{
	return coordinates;
}

void Lane::add_car(Car const &car, int coordinate)
{
	cars.push_back(car);
	coordinates.push_back(coordinate);
}