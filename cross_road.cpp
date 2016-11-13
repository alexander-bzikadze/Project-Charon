#include <cstdint>
#include <set>

#include "cross_road.hpp"

using namespace std;

Cross_road::Cross_road(size_t time_to_cross_crossroad) :
	builded(false)
{
	for (size_t i = 0; i < time_to_cross_crossroad; ++i)
	{
		number_of_added_cars.push(0);
	}
}

Cross_road::Cross_road(size_t time_to_cross_crossroad, Traffic_light const& traffic_light) : 
	traffic_light(traffic_light) ,
	builded(false)
{
	for (size_t i = 0; i < time_to_cross_crossroad; ++i)
	{
		number_of_added_cars.push(0);
	}
}


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
	return traffic_light_result == 0;
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

void Cross_road::standard_build(vector<Side*> sides)
{
	const static size_t expected = 8;
	if (builded)
	{
		//throw something
		return;
	}
	if (sides.size() != expected)
	{
		//throw something
		return;
	}
	for (size_t i = 1; i < sides.size(); ++i)
	{
		if (sides[i]->get_lanes().size() != sides[i - 1]->get_lanes().size())
		{
			//throw something
			return;
		}
	}
	size_t max_status = 2;
	std::vector <std::unordered_map <Lane*, std::unordered_map <Lane*, size_t>>> road_status;
	road_status.resize(max_status);
	for (size_t i = 0; i < expected; i += 2)
	{
		size_t current_road_status = (i % 4) / 2;
		size_t anti_current_road_status = ((i % 4) / 2 + 1) % 2;
		auto left = &sides[i]->get_lanes()[0];
		auto right = &sides[i]->get_lanes()[sides[i]->get_lanes().size() - 1];
		auto destination_of_left = &sides[(i + 5) % expected]->get_lanes()[0];
		auto destination_of_right = &sides[(i + 3) % expected]->get_lanes()[sides[i]->get_lanes().size() - 1];
		// road_status[0][left]
		this->lane_connections[left][sides[(i + 5) % expected]] = destination_of_left;
		this->lane_connections[right][sides[(i + 3) % expected]] = destination_of_right;
		road_status[current_road_status][left][destination_of_left] = 1;
		road_status[current_road_status][right][destination_of_right] = 1;
		road_status[anti_current_road_status][left][destination_of_left] = 2;
		road_status[anti_current_road_status][right][destination_of_right] = 2;
		for (size_t j = 0; j < sides[i]->get_lanes().size(); ++j)
		{
			auto current_lane = &sides[i]->get_lanes()[j];
			auto current_lane_destination = &sides[(i + 4) % expected]->get_lanes()[j];
			this->lane_connections[current_lane][sides[(i + 4) % expected]] = current_lane_destination;
			road_status[current_road_status][current_lane][current_lane_destination] = 0;
			road_status[anti_current_road_status][current_lane][current_lane_destination] = 2;
		}
		this->outgoing_sides.push_back(sides[i + 1]);
		sides[i]->build(this);
	}
	size_t added_lanes = 0;
	for (size_t i = 0; i < expected; ++i)
	{
		for (size_t j = 0; j < sides[i]->get_lanes().size(); ++j)
		{
			this->number_of_lanes_in_clock_order[&sides[i]->get_lanes()[j]] = added_lanes++;
		}
	}
	this->traffic_light = Traffic_light(max_status, road_status);
}