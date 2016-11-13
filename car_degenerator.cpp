#include "car_degenerator.hpp"

using namespace std;

void Car_degenerator::update()
{
	for (auto x : cars_to_delete)
	{
		delete x;
	}
	cars_to_delete.clear();
}

bool Car_degenerator::can_go(Lane* const original_lane, Side* const new_side)
{
	if (new_side != nullptr)
	{
		//throw something
	}
	return true;
}

void Car_degenerator::go(Car* car, Lane* original_lane, Side* const new_side)
{
	if (new_side != nullptr)
	{
		//throw something
	}
	cars_to_delete.push_back(car);
}