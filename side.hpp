#pragma once

#include <vector>
#include <ostream>
#include <queue>

#include "lane.hpp"
#include "car.hpp"

class Side
{
public:
	Side() = default;

	Side(size_t road_length, size_t lane_number);

	Side(size_t road_length, size_t lane_number, 
		size_t recommended_speed, size_t safe_distance);

	void update();
	void print() const;

	Car const* get_car(size_t i, size_t j) const;

	bool can_add_to_lane(size_t lane_number) const;
	void add_to_lane(Car* car, size_t lane_number);

	std::vector<Lane>& get_lanes();

private:
	bool can_switch_lanes(size_t lane_number, size_t car_number, size_t new_lane_number) const;

	const size_t road_length;
	const size_t recommended_speed;
	const size_t safe_distance;

	std::vector<Lane> lanes;
	std::vector<size_t> coordinates_of_cars_to_update;
	std::priority_queue<std::pair<size_t, size_t>> cars_to_update;
};