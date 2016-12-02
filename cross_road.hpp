#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <cstdint>

#include "icross_road.hpp"
#include "side.hpp"
#include "lane.hpp"
#include "car.hpp"

/// Standart implementation of ICross_road.
/// Besides ICross_road methodes, can be builded.
/// It is invaled to use ICross_road when its not builed.
class Cross_road : public ICross_road
{
public:
	Cross_road() = default;
	Cross_road(size_t time_to_cross_crossroad);

	bool can_go(std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side) override;

	void go(std::unique_ptr<Car>&& car, std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side) override;

	void update() override;

	/// Takes 8 sized vector of sides and builds standart crossroad:
	/// from each incoming side one may turn to the left of right of go straightly.
	void standard_build(std::vector< std::shared_ptr<Side> > sides);

	std::vector< std::shared_ptr<Side>> const& get_outgoing_sides() const;

private:
	class Traffic_light
	{
	public:
		enum class Availiable_lights : std::uint8_t { main_road, secondary_road, stop_road };
		Traffic_light() = default;
		Traffic_light(size_t max_status);
		Traffic_light(size_t max_status, std::vector <std::unordered_map <std::shared_ptr<Lane>, std::unordered_map <std::shared_ptr<Lane>, Availiable_lights>>> road_status);
		Traffic_light(Traffic_light const& copied);
		Traffic_light operator=(Traffic_light const& x);


		std::vector< std::pair <std::shared_ptr<Lane>, std::shared_ptr<Lane>>> get_main_roads();
		std::vector< std::pair <std::shared_ptr<Lane>, std::shared_ptr<Lane>>> get_active_roads();
		Availiable_lights get_status(std::shared_ptr<Lane> const original_lane, std::shared_ptr<Lane> const new_lane);
		void update();


	private:
		size_t max_status = 0;
		size_t current_status;
		size_t max_time = 60;
		size_t current_time;

		std::vector <std::unordered_map <std::shared_ptr<Lane>, std::unordered_map <std::shared_ptr<Lane>, Availiable_lights>>> road_status;
	};

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