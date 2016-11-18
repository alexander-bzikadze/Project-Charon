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
	Traffic_light(size_t max_status, std::vector <std::unordered_map <std::shared_ptr<Lane>, std::unordered_map <std::shared_ptr<Lane>, size_t>>> road_status);
	Traffic_light(Traffic_light const& copied);
	Traffic_light operator=(Traffic_light const& x);

	std::vector< std::pair <std::shared_ptr<Lane>, std::shared_ptr<Lane>>> get_main_roads();
	std::vector< std::pair <std::shared_ptr<Lane>, std::shared_ptr<Lane>>> get_active_roads();
	int8_t get_status(std::shared_ptr<Lane> const original_lane, std::shared_ptr<Lane> const new_lane);
	void update();

private:
	size_t max_status = 0;
	size_t current_status;
	size_t max_time = 60;
	size_t current_time;

	std::vector <std::unordered_map <std::shared_ptr<Lane>, std::unordered_map <std::shared_ptr<Lane>, size_t>>> road_status;
};