#include "car_degenerator.hpp"
#include "exceptions.hpp"

#include <iostream>
using namespace std;

void Car_degenerator::update()
{
	cars_to_delete.clear();
}

bool Car_degenerator::can_go(shared_ptr<Lane> original_lane, shared_ptr<Side> new_side)
{
	if (new_side != nullptr)
	{
		throw Car_is_not_to_be_deleted("Cannot delete car in Car_degenerator as it shall go on living");
	}
	return true;
}

void Car_degenerator::go(unique_ptr<Car>&& car, shared_ptr<Lane> original_lane, shared_ptr<Side> new_side)
{
	if (new_side != nullptr)
	{
		throw Car_is_not_to_be_deleted("Cannot delete car in Car_degenerator as it shall go on living");
	}
	cars_to_delete.emplace_back(move(car));
}

vector< unique_ptr<Car> > const& Car_degenerator::get_cars_to_delete()
{
	return cars_to_delete;
}