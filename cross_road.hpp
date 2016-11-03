#pragma once

#include "side.hpp"
#include "lane.hpp"
#include "car.hpp"

#include <vector>
#include <unordered_map>
#include <queue>

class Cross_road
{
public:
	bool can_go(Lane* const original_lane, Side* const new_side);

	void go(Car const& car, Lane const& original_lane, Side const& new_side);

private:
	//traffic_light

	// std::vector<Side*> incoming_sides;
	// std::vector<Side*> outgoing_sides;

	std::unordered_map<Lane*, size_t> number_of_lanes_in_clock_order;

	const size_t time_to_cross_crossroad = 3;

	std::unordered_map<Lane*, std::unordered_map<Side*, Lane*>> lane_connections;

	std::queue<size_t> number_of_added_cars;
	std::vector<std::pair<std::pair<Lane*,Lane*>, size_t>> cars_in_crossroad_with_time;
};

// size_t t = 100; while (t-- > -1); - в 64 битной size_t размера 8 байт ==> -1 как 32-битный литерал приведется к самому большому 64-битному числу.