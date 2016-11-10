#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>

#include "lane.hpp"

class Traffic_light
{
public:
	Traffic_light() = default;
	Traffic_light(size_t max_status);

	std::vector< std::pair <Lane*, Lane*>> get_main_roads();
	int8_t get_status(Lane* const original_lane, Lane* const new_lane);
	void update();

private:
	const size_t max_status;
	size_t current_status;

	std::vector <std::unordered_map <Lane*, std::unordered_map <Lane*, size_t>>> road_status;
};