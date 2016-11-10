#pragma once

#include <vector>
#include <unordered_map>
#include <queue>

#include "side.hpp"
#include "traffic_light.hpp"
#include "lane.hpp"
#include "car.hpp"

class Cross_road
{
public:
	bool can_go(Lane* const original_lane, Side* const new_side);

	void go(Car* car, Lane* original_lane, Side* const new_side);

	void update();

private:
	Traffic_light traffic_light;

	// std::vector<Side*> incoming_sides;
	// std::vector<Side*> outgoing_sides;

	std::unordered_map<Lane*, size_t> number_of_lanes_in_clock_order;

	const size_t time_to_cross_crossroad = 3;

	std::unordered_map<Lane*, std::unordered_map<Side*, Lane*>> lane_connections;

	std::queue<size_t> number_of_added_cars;
	std::vector<std::pair<std::pair<Lane*, Lane*>, Car*>> cars_in_crossroad_with_time;
};