#include "traffic_light.hpp"

using namespace std;

Traffic_light::Traffic_light(size_t max_status) :
	max_status(max_status) ,
	current_status(0)
	{}

Traffic_light::Traffic_light(Traffic_light const& copied) :
	max_status(copied.max_status) ,
	current_status(copied.current_status)
{
	road_status = copied.road_status;
}

Traffic_light::Traffic_light(size_t max_status, std::vector <std::unordered_map <Lane*, std::unordered_map <Lane*, size_t>>> road_status) :
	max_status(max_status) ,
	road_status(road_status)
	{}

Traffic_light Traffic_light::operator=(Traffic_light const& x)
{
	max_status = x.max_status;
	current_status = x.current_status;
	road_status = x.road_status;
	return *this;
}

// 0 - main, 1 - sub, 2 - forbidden.
vector <pair< Lane*, Lane*>> Traffic_light::get_main_roads()
{
	vector <pair <Lane*, Lane*>> main_roads;
	for (auto i = road_status[current_status].begin(); i != road_status[current_status].end(); ++i)
	{
		for (auto j = i->second.begin(); j != i->second.end(); ++j)
		{
			if (j->second == 0)
			{
				main_roads.push_back({i->first, j->first});
			}
		}
	}
	return main_roads;
}

int8_t Traffic_light::get_status(Lane* const original_lane, Lane* const new_lane)
{
	return road_status[current_status][original_lane][new_lane];
}

void Traffic_light::update()
{
	current_status++;
	if (current_status == max_status)
	{
		current_status = 0;
	}
}