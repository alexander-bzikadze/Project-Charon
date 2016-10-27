#include <algorithm>
#include <iostream>

#include "car.hpp"

int Car::update(int nearest_barrier, 
		int nearest_barrier_speed,
		int update_frequency,
		int recommended_speed,
		int safe_distance)
{
	if (nearest_barrier < critical_distance)
	{
		if (speed != 0)
		{
			// throw something
		}
		return 0;
	}
	int passed_distance = 0;
	int previous_speed = speed;
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
	return passed_distance;
}

int Car::get_speed() const
{
	return speed;
}

int Car::get_size() const
{
	return car_size;
}