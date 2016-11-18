#include "cross_road.hpp"
#include <iostream>

using namespace std;

Cross_road::Traffic_light::Traffic_light(size_t max_status) :
	max_status(max_status) ,
	current_status(0) ,
	max_time(60) ,
	current_time(0)
	{}

Cross_road::Traffic_light::Traffic_light(Traffic_light const& copied) :
	max_status(copied.max_status) ,
	current_status(copied.current_status) ,
	max_time(copied.max_time) ,
	current_time(copied.current_time)
{
	road_status = copied.road_status;
}

Cross_road::Traffic_light::Traffic_light(size_t max_status, std::vector <std::unordered_map <std::shared_ptr<Lane>, std::unordered_map <std::shared_ptr<Lane>, Availiable_lights>>> road_status) :
	max_status(max_status) ,
	current_status(0) ,
	max_time(60) ,
	current_time(0) ,
	road_status(road_status)
	{}

Cross_road::Traffic_light Cross_road::Traffic_light::operator=(Traffic_light const& x)
{
	max_status = x.max_status;
	current_status = x.current_status;
	max_time = x.max_time;
	current_time = x.current_time;
	road_status = x.road_status;
	return *this;
}

// 0 - main, 1 - sub, 2 - forbidden.
vector <pair< std::shared_ptr<Lane>, std::shared_ptr<Lane>>> Cross_road::Traffic_light::get_main_roads()
{
	vector <pair <std::shared_ptr<Lane>, std::shared_ptr<Lane>>> main_roads;
	for (auto i = road_status[current_status].begin(); i != road_status[current_status].end(); ++i)
	{
		for (auto j = i->second.begin(); j != i->second.end(); ++j)
		{
			if (j->second == Availiable_lights::main_road)
			{
				main_roads.push_back({i->first, j->first});
			}
		}
	}
	return main_roads;
}

vector <pair< std::shared_ptr<Lane>, std::shared_ptr<Lane>>> Cross_road::Traffic_light::get_active_roads()
{
	vector <pair <std::shared_ptr<Lane>, std::shared_ptr<Lane>>> main_roads;
	for (auto i = road_status[current_status].begin(); i != road_status[current_status].end(); ++i)
	{
		for (auto j = i->second.begin(); j != i->second.end(); ++j)
		{
			if (j->second != Availiable_lights::stop_road)
			{
				main_roads.push_back({i->first, j->first});
			}
		}
	}
	return main_roads;
}

Cross_road::Traffic_light::Availiable_lights Cross_road::Traffic_light::get_status(std::shared_ptr<Lane> const original_lane, std::shared_ptr<Lane> const new_lane)
{
	return road_status[current_status][original_lane][new_lane];
}

void Cross_road::Traffic_light::update()
{
	current_time++;
	if (current_time == max_time)
	{
		current_time = 0;
		current_status++;
		if (current_status == max_status)
		{
			current_status = 0;
		}
	}
}