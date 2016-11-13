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
	Cross_road() = default;
	Cross_road(size_t time_to_cross_crossroad);
	Cross_road(size_t time_to_cross_crossroad, Traffic_light const& traffic_light);

	bool can_go(Lane* const original_lane, Side* const new_side);

	void go(Car* car, Lane* original_lane, Side* const new_side);

	void update();

	void standard_build(std::vector<Side*> sides);

private:
	Traffic_light traffic_light;
	bool builded;

	// std::vector<Side*> incoming_sides;
	// std::vector<Side*> outgoing_sides;

	std::unordered_map<Lane*, size_t> number_of_lanes_in_clock_order;

	std::unordered_map<Lane*, std::unordered_map<Side*, Lane*>> lane_connections;

	std::queue<size_t> number_of_added_cars;
	std::vector<std::pair<std::pair<Lane*, Lane*>, Car*>> cars_in_crossroad_with_time;
};