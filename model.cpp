#include "model.hpp"

using namespace std;

Model::Model(vector<shared_ptr<Side>>& sides, 
			vector<shared_ptr<Car_generator>>& car_generators,
			vector<shared_ptr<Cross_road>>& cross_roads,
			vector<shared_ptr<Car_degenerator>>& car_degenerators) :
	sides(sides) ,
	car_generators(car_generators) ,
	cross_roads(cross_roads) ,
	car_degenerators(car_degenerators)
{}

void Model::update()
{	
	for (auto car_degenerator : car_degenerators)
	{
		car_degenerator->update();
	}	
	for (auto car_generator : car_generators)
	{
		car_generator->update();
	}
	for (auto side : sides)
	{
		side->update();
	}
	for (auto cross_road : cross_roads)
	{
		cross_road->update();
	}
}

vector<shared_ptr<Side>> const& Model::get_sides() const
{
	return sides;
}

vector<shared_ptr<Car_generator>> const& Model::get_car_generators() const
{
	return car_generators;
}

vector<shared_ptr<Cross_road>> const& Model::get_cross_roads() const
{
	return cross_roads;
}

vector<shared_ptr<Car_degenerator>> const& Model::get_car_degenerators() const
{
	return car_degenerators;
}

void Model::call_event_car_added(Car* car_pointer)
{
	emit event_car_added(car_pointer);
}
