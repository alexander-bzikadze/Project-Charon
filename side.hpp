#pragma once

#include <vector>
#include <ostream>
#include <queue>

#include "lane.hpp"
#include "car.hpp"

class ICross_road;

class Side
{
public:
	Side() = default;

	Side(size_t road_length, size_t lane_number);

	Side(size_t road_length, size_t lane_number, 
		size_t recommended_speed, size_t safe_distance);

	void update();
	void print() const;

	bool can_add_to_lane(size_t lane_number) const;
	bool can_add_to_lane(std::shared_ptr<Lane> lane) const;
	void add_to_lane(std::unique_ptr<Car>&& car, size_t lane_number);

	void build(ICross_road* destination);

	std::vector<std::shared_ptr<Lane>>& get_lanes();

private:
	bool can_switch_lanes(size_t lane_number, size_t car_number, size_t new_lane_number) const;
	bool builded;

	const size_t road_length;
	const size_t recommended_speed;
	const size_t safe_distance;

	ICross_road* destination;
	std::vector<std::shared_ptr<Lane>> lanes;
	std::vector<size_t> coordinates_of_cars_to_update;
	std::priority_queue<std::pair<size_t, size_t>> cars_to_update;
};