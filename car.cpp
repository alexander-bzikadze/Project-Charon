#include <algorithm>
#include <iostream>

#include "car.hpp"

Car::Car(size_t coordinate) :
	coordinate(coordinate)
	{}

void Car::update(size_t nearest_barrier_coordinate, 
		size_t nearest_barrier_speed,
		size_t update_frequency,
		size_t recommended_speed,
		size_t safe_distance)
{
	size_t nearest_barrier = nearest_barrier_coordinate - coordinate;
	if (nearest_barrier < critical_distance)
	{
		if (speed != 0)
		{
			// throw something
		}
		return;
	}
	size_t passed_distance = 0;
	size_t previous_speed = speed;
	if (nearest_barrier <= safe_distance)
	{
		speed = (nearest_barrier / update_frequency) - previous_speed;
	}
	else if (nearest_barrier <= safe_distance * 2)
	{
		speed = 2 * (nearest_barrier - safe_distance) / update_frequency - previous_speed;
	}
	else
	{
		speed = recommended_speed;
	}
	passed_distance = (speed + previous_speed) / 2 * update_frequency;
	coordinate += passed_distance;
}

size_t Car::get_speed() const
{
	return speed;
}

size_t Car::get_size() const
{
	return car_size;
}

size_t Car::get_coordinate() const
{
	return coordinate;
}