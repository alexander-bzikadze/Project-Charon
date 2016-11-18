#include "car_degenerator.hpp"

#include <iostream>
using namespace std;

void Car_degenerator::update()
{
	cars_to_delete.clear();
}

bool Car_degenerator::can_go(std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side)
{
	if (new_side != nullptr)
	{
		//throw something
	}
	return true;
}

void Car_degenerator::go(unique_ptr<Car>&& car, std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side)
{
	if (new_side != nullptr)
	{
		//throw something
	}
	cars_to_delete.push_back(move(car));
}