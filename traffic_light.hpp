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
	Traffic_light(size_t max_status, std::vector <std::unordered_map <Lane*, std::unordered_map <Lane*, size_t>>> road_status);
	Traffic_light(Traffic_light const& copied);
	Traffic_light operator=(Traffic_light const& x);

	std::vector< std::pair <Lane*, Lane*>> get_main_roads();
	int8_t get_status(Lane* const original_lane, Lane* const new_lane);
	void update();

private:
	size_t max_status = 0;
	size_t current_status;

	std::vector <std::unordered_map <Lane*, std::unordered_map <Lane*, size_t>>> road_status;
};