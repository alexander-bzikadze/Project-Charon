#include "car_generator.hpp"

#include <iostream>

using namespace std;

Car_generator::Car_generator(std::shared_ptr<Side> outgoing_side) :
	outgoing_side(outgoing_side)
	{}

Car_generator::Car_generator(std::shared_ptr<Side> outgoing_side, const std::vector< std::shared_ptr<Side> >& path) :
	outgoing_side(outgoing_side) ,
	path((new vector<shared_ptr<Side>>(path)))
	{}

void Car_generator::update()
{
	current_interval++;
	if (current_interval == interval && outgoing_side->can_add_to_lane(0))
	{
		current_interval = 0;
		outgoing_side->add_to_lane(unique_ptr<Car>(new Car(path)), 0);
	}
}

shared_ptr<Side> const Car_generator::get_outgoing_side() const
{
	return outgoing_side;
}