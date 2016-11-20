#include "car.hpp"
#include "exceptions.hpp"

using namespace std;

Car::Car(size_t coordinate) :
	path_to_pass(0) ,
	coordinate(coordinate) ,
	speed(0)
	{}

Car::Car(std::shared_ptr< vector< std::shared_ptr<Side> >> const& path) :
	path(path) ,
	path_to_pass(path->size() - 1) ,
	coordinate(0) ,
	speed(0)
	{}

Car::Car(Car const& car) :
	path(car.path) ,
	path_to_pass(car.path_to_pass) ,
	coordinate(car.coordinate) ,
	speed(car.speed)
	{}

Car& Car::operator=(Car const& copied)
{
	path = copied.path;
	path_to_pass = copied.path_to_pass;
	coordinate = copied.coordinate;
	speed = copied.speed;
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
			throw Car_crossed_barrier("Not zero speed but nearest_barrier is less than critical_distance");
		}
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
	if (path == nullptr)
	{
		throw Model_object_is_not_built("Car is not built");
	}
	if (path->size() == 0)
	{
		throw Car_path_size_is_not_positive("Car path size is 0 toping back");
	}
	return (*path)[path_to_pass];
}

void Car::go()
{
	if (path == nullptr)
	{
		throw Model_object_is_not_built("Car is not built");
	}
	if (path->size() == 0)
	{
		throw Car_path_size_is_not_positive("Car path size is 0 when poping back");
	}
	coordinate = 0;
	path_to_pass--;
}