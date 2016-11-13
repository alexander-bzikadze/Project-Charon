#include "car_generator.hpp"

using namespace std;

Car_generator::Car_generator(Side* outgoing_side, std::vector<Side*> path) :
	outgoing_side(outgoing_side) ,
	path(path)
	{}

void Car_generator::update()
{
	if (outgoing_side->can_add_to_lane(0))
	{
		outgoing_side->add_to_lane(new Car(path), 0);
	}
}

bool Car_generator::can_go(Lane* const original_lane, Side* const new_side)
{
	//throw something
	return false;
}

void Car_generator::go(Car* car, Lane* original_lane, Side* const new_side)
{
	//throw something
}