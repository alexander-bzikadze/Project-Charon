#include <cstdint>
#include <set>

#include <iostream>

#include "cross_road.hpp"

using namespace std;

Cross_road::Cross_road(size_t time_to_cross_crossroad) :
	builded(false)
{
	for (size_t i = 0; i < time_to_cross_crossroad; ++i)
	{
		number_of_cars_in_cross_road.push(0);
	}
}


bool Cross_road::can_go(std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side)
{
	if (lane_connections.at(original_lane).find(new_side) == lane_connections.at(original_lane).end())
	{
		return false;
	}
	std::shared_ptr<Lane> const new_lane = lane_connections[original_lane][new_side];
	// int8_t traffic_light_result = 1; // 0 or 2
	if (!new_side->can_add_to_lane(new_lane))
	{
		return false;
	}
	Traffic_light::Availiable_lights traffic_light_result = traffic_light.get_status(original_lane, new_lane);
	if (traffic_light_result == Traffic_light::Availiable_lights::secondary_road)
	{
		std::vector<std::pair<std::shared_ptr<Lane>, std::shared_ptr<Lane>>> const main_roads = traffic_light.get_active_roads();
		// std::vector<std::pair<Lane*, Lane*>> const main_roads;
		std::set<std::pair<std::shared_ptr<Lane>, std::shared_ptr<Lane>>> crossed_roads;
		for (auto x : main_roads)
		{
			if ((number_of_lanes_in_clock_order[original_lane] <= number_of_lanes_in_clock_order[x.first]
				&& number_of_lanes_in_clock_order[new_lane] >= number_of_lanes_in_clock_order[x.second])
				|| (number_of_lanes_in_clock_order[original_lane] >= number_of_lanes_in_clock_order[x.first]
				&& number_of_lanes_in_clock_order[new_lane] <= number_of_lanes_in_clock_order[x.second]))
			{
				crossed_roads.insert(x);
			}
		}
		bool result = true;
		for (const auto &x : cars_in_cross_road_paths)
		{
			result &= (crossed_roads.find(x) == crossed_roads.end());
			if (!result)
			{
				break;
			}
		}
		return result;
	}
	return traffic_light_result == Traffic_light::Availiable_lights::main_road;
}

void Cross_road::go(unique_ptr<Car>&& car, std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side)
{
	std::shared_ptr<Lane> new_lane = lane_connections[original_lane][new_side];
	pair<shared_ptr<Lane>, shared_ptr<Lane>> added_path = {original_lane, new_lane};
	cars_in_cross_road_paths.push_back(added_path);
	cars_in_cross_road.push_back(move(car));
	number_of_cars_in_cross_road.back()++;
}

void Cross_road::update()
{
	size_t number_of_cars_to_delete = number_of_cars_in_cross_road.front();
	number_of_cars_in_cross_road.pop();
	number_of_cars_in_cross_road.push(0);
	for (size_t i = 0; i < number_of_cars_to_delete; ++i)
	{
		cars_in_cross_road[i]->go();
		cars_in_cross_road_paths[i].second->add_car(move(cars_in_cross_road[i]));
	}
	cars_in_cross_road.erase(cars_in_cross_road.begin(), cars_in_cross_road.begin() + number_of_cars_to_delete);
	cars_in_cross_road_paths.erase(cars_in_cross_road_paths.begin(), cars_in_cross_road_paths.begin() + number_of_cars_to_delete);
	traffic_light.update();
}

void Cross_road::standard_build(vector<std::shared_ptr<Side>> sides)
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
	std::vector <std::unordered_map <shared_ptr<Lane>, std::unordered_map <shared_ptr<Lane>, Traffic_light::Availiable_lights>>> road_status;
	road_status.resize(max_status);
	for (size_t i = 0; i < expected; i += 2)
	{
		size_t current_road_status = (i % 4) / 2;
		size_t anti_current_road_status = ((i % 4) / 2 + 1) % 2;
		shared_ptr<Lane> left = sides[i]->get_lanes()[0];
		shared_ptr<Lane> right = sides[i]->get_lanes()[sides[i]->get_lanes().size() - 1];
		shared_ptr<Lane> destination_of_left = sides[(i + 5) % expected]->get_lanes()[0];
		shared_ptr<Lane> destination_of_right = sides[(i + 1) % expected]->get_lanes()[sides[i]->get_lanes().size() - 1];
		this->lane_connections[left][sides[(i + 5) % expected]] = destination_of_left;
		this->lane_connections[right][sides[(i + 1) % expected]] = destination_of_right;
		road_status[current_road_status][left][destination_of_left] = Traffic_light::Availiable_lights::secondary_road;
		road_status[current_road_status][right][destination_of_right] = Traffic_light::Availiable_lights::secondary_road;
		road_status[anti_current_road_status][left][destination_of_left] = Traffic_light::Availiable_lights::stop_road;
		road_status[anti_current_road_status][right][destination_of_right] = Traffic_light::Availiable_lights::stop_road;
		for (size_t j = 0; j < sides[i]->get_lanes().size(); ++j)
		{
			shared_ptr<Lane> current_lane = sides[i]->get_lanes()[j];
			shared_ptr<Lane> current_lane_destination = sides[(i + 3) % expected]->get_lanes()[j];
			this->lane_connections[current_lane][sides[(i + 3) % expected]] = current_lane_destination;
			road_status[current_road_status][current_lane][current_lane_destination] = Traffic_light::Availiable_lights::main_road;
			road_status[anti_current_road_status][current_lane][current_lane_destination] = Traffic_light::Availiable_lights::stop_road;
		}
		this->outgoing_sides.push_back(sides[i + 1]);
		sides[i]->build(this);
	}
	size_t added_lanes = 0;
	for (size_t i = 0; i < expected; ++i)
	{
		for (size_t j = 0; j < sides[i]->get_lanes().size(); ++j)
		{
			this->number_of_lanes_in_clock_order[sides[i]->get_lanes()[j]] = added_lanes++;
		}
	}
	this->traffic_light = Traffic_light(max_status, road_status);
}

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