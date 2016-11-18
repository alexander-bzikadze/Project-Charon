#include "car_generator.hpp"

#include <iostream>

using namespace std;

Car_generator::Car_generator(std::shared_ptr<Side> outgoing_side) :
	outgoing_side(outgoing_side)
	{}

Car_generator::Car_generator(std::shared_ptr<Side> outgoing_side, const std::vector< std::shared_ptr<Side> >& path) :
	outgoing_side(outgoing_side) ,
	path(path)
	{}

void Car_generator::update()
{
	if (outgoing_side->can_add_to_lane(0))
	{
		outgoing_side->add_to_lane(unique_ptr<Car>(new Car(path)), 0);
	}
}

bool Car_generator::can_go(std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side)
{
	//throw something
	return false;
}

void Car_generator::go(unique_ptr<Car>&& car, std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side)
{
	//throw something
}