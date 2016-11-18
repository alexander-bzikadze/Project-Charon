#include "lane.hpp"

#include <iostream>

using namespace std;

void Lane::update_car(size_t road_length, size_t const recommended_speed, size_t const safe_distance, size_t const index)
{
	if (cars.size() == 0)
	{
		return;
	}
	if (index == 0)
	{
		cars[0]->update(road_length, 0, 1, 
			recommended_speed, safe_distance);
	}
	else
	{
		cars[index]->update(cars[index - 1]->get_coordinate()
			- cars[index - 1]->get_size(), cars[index - 1]->get_speed(), 1,
			recommended_speed, safe_distance);
	}
}

std::vector< unique_ptr<Car> > const& Lane::get_cars() const
{
	return cars;
}

void Lane::add_car(unique_ptr<Car>&& car)
{	
	cars.push_back(std::move(car));
}

Car* Lane::go_car(size_t road_length)
{
	number_of_cars_to_delete++;
	auto went_car = move(cars[0]);
	cars[0] = unique_ptr<Car>(new Car(road_length));
	return went_car.release();
}

void Lane::update()
{
	if (number_of_cars_to_delete)
	{
		cars.erase(cars.begin(), cars.begin() + number_of_cars_to_delete);
		number_of_cars_to_delete = 0;
	}
}