#include <cstdint>
#include <set>

#include "cross_road.hpp"

using namespace std;

bool Cross_road::can_go(Lane* const original_lane, Side* const new_side)
{
	if (lane_connections.at(original_lane).find(new_side) == lane_connections.at(original_lane).end())
	{
		return false;
	}
	Lane* const new_lane = lane_connections[original_lane][new_side];
	// int8_t traffic_light_result = 1; // 0 or 2
	int8_t traffic_light_result = traffic_light.get_status(original_lane, new_lane);
	if (traffic_light_result == 1)
	{
		std::vector<std::pair<Lane*, Lane*>> const main_roads = traffic_light.get_main_roads();
		// std::vector<std::pair<Lane*, Lane*>> const main_roads;
		std::set<std::pair<Lane*, Lane*>> crossed_roads;
		for (auto x : main_roads)
		{
			if ((number_of_lanes_in_clock_order[original_lane] < number_of_lanes_in_clock_order[x.first]
				&& number_of_lanes_in_clock_order[new_lane] > number_of_lanes_in_clock_order[x.second])
				|| (number_of_lanes_in_clock_order[original_lane] > number_of_lanes_in_clock_order[x.first]
				&& number_of_lanes_in_clock_order[new_lane] < number_of_lanes_in_clock_order[x.second]))
			{
				crossed_roads.insert(x);
			}
		}
		bool result = true;
		for (auto x : cars_in_crossroad_with_time)
		{
			result |= (crossed_roads.find(x.first) != crossed_roads.end());
			if (!result)
			{
				break;
			}
		}
		return result;
	}
	return traffic_light_result != 0;
}

void Cross_road::go(Car* car, Lane* original_lane, Side* const new_side)
{
	Lane* new_lane = lane_connections[original_lane][new_side];
	pair <pair <Lane*, Lane*>, Car*> added_cars_lanes_and_time;
	added_cars_lanes_and_time.first.first = original_lane;
	added_cars_lanes_and_time.first.second = new_lane;
	added_cars_lanes_and_time.second = car;
	cars_in_crossroad_with_time.push_back(added_cars_lanes_and_time);
	number_of_added_cars.back()++;
}

void Cross_road::update()
{
	size_t number_of_cars_to_delete = number_of_added_cars.front();
	number_of_added_cars.pop();
	number_of_added_cars.push(0);
	for (size_t i = 0; i < number_of_cars_to_delete; ++i)
	{
		auto added_car = cars_in_crossroad_with_time[i];
		added_car.first.second->add_car(added_car.second);
	}
	cars_in_crossroad_with_time.erase(cars_in_crossroad_with_time.begin(), cars_in_crossroad_with_time.begin() + number_of_cars_to_delete);
}

