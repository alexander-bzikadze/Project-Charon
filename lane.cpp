#include "lane.hpp"

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

std::vector<Car*> const& Lane::get_cars() const
{
	return cars;
}

void Lane::add_car(Car* car)
{
	cars.push_back(car);
}