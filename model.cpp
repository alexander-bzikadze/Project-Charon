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
	for (auto& x : car_degenerators)
	{
		x->update();
	}
	for (auto& x : car_generators)
	{
		x->update();
	}
	for (auto& x : sides)
	{
		x->update();
	}
	for (auto& x : cross_roads)
	{
		x->update();
	}
}