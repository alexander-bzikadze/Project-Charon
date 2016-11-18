#pragma once

#include <vector>
#include <unordered_map>
#include <queue>

#include "icross_road.hpp"
#include "side.hpp"
#include "traffic_light.hpp"
#include "lane.hpp"
#include "car.hpp"

class Cross_road : public ICross_road
{
public:
	Cross_road() = default;
	Cross_road(size_t time_to_cross_crossroad);
	Cross_road(size_t time_to_cross_crossroad, Traffic_light const& traffic_light);

	bool can_go(std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side) override;

	void go(std::unique_ptr<Car>&& car, std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side) override;

	void update() override;

	void standard_build(std::vector< std::shared_ptr<Side> > sides);

private:
	Traffic_light traffic_light;
	bool builded;

	// std::vector<Side*> incoming_sides;
	std::vector< std::shared_ptr<Side> > outgoing_sides;

	std::unordered_map<std::shared_ptr<Lane>, size_t> number_of_lanes_in_clock_order;

	std::unordered_map<std::shared_ptr<Lane>, std::unordered_map<std::shared_ptr<Side>, std::shared_ptr<Lane>>> lane_connections;

	std::queue<size_t> number_of_cars_in_cross_road;
	std::vector< std::unique_ptr<Car> > cars_in_cross_road;
	std::vector< std::pair<std::shared_ptr<Lane>, std::shared_ptr<Lane>> > cars_in_cross_road_paths;
};