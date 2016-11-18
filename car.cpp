#include <algorithm>
#include <iostream>

#include "car.hpp"

using namespace std;

Car::Car(size_t coordinate) :
	coordinate(coordinate) ,
	speed(0)
	{}

Car::Car(vector< std::shared_ptr<Side> > const& path) :
	path(path) ,
	coordinate(0) ,
	speed(0)
	{}

Car::Car(Car const& car) :
	path(car.path) ,
	coordinate(car.coordinate) ,
	speed(car.speed)
	{}

Car& Car::operator=(Car const& copied)
{
	coordinate = copied.coordinate;
	speed = copied.speed;
	path = copied.path;
	return *this;
}

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
	if (nearest_barrier <= 2 * safe_distance)
	{
		speed = (nearest_barrier / update_frequency) - previous_speed;
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

shared_ptr<Side> Car::where_to_go() const
{
	if (path.size() == 0)
	{
		//throw something
		return nullptr;
	}
	return path[path.size() - 1];
}

void Car::go()
{
	if (path.size() == 0)
	{
		//throw something
		return;
	}
	coordinate = 0;
	path.pop_back();
}