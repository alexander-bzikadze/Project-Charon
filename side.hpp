#pragma once

#include <vector>
#include <queue>

#include "lane.hpp"
#include "car.hpp"

class ICross_road;

/// A class to hold lanes.
/// Basic meaning is one-sided road with n lanes. Two sides make a two-sided road.
/// Holds its lanes, length, recommeded_speed and safe_distance.
/// Also has pointer to its final destiantion - ICross_road.
class Side
{
public:
	/// Default constructor.
	Side() = default;

	/// Constructor with initialized length and number of lanes.
	/// Recommended speed and safe distanse are initialized as 20.
	Side(size_t road_length, size_t lane_number);

	/// Constructor with all specified values.
	Side(size_t road_length, size_t lane_number, 
		size_t recommended_speed, size_t safe_distance);

	/// Updates cars in all lanes. Cars are chosed by maximum of coordinates.
	void update();

	/// Prints all cars in lanes.
	void print() const;

	/// Returns result of can anything be added to the lane with specified number. Constatant complexity.
	bool can_add_to_lane(size_t lane_number) const;

	/// Returns result of can anything be added to given lane. Linear complexity.
	bool can_add_to_lane(std::shared_ptr<Lane> lane) const;

	/// Adds given car to specified lane.
	void add_to_lane(std::unique_ptr<Car>&& car, size_t lane_number);

	/// Builds side. Means that specifies destination.
	/// If side is not builded, its invalid to use it.
	void build(ICross_road* destination);

	/// Returns vector of all lanes by reference.
	std::vector<std::shared_ptr<Lane>>& get_lanes();

	ICross_road* get_destination() const;
	size_t get_road_length() const;

private:
	bool can_switch_lanes(size_t lane_number, size_t car_number, size_t new_lane_number) const;
	bool builded;

	const size_t road_length;
	const size_t recommended_speed = 20;
	const size_t safe_distance = 20;

	ICross_road* destination;
	std::vector<std::shared_ptr<Lane>> lanes;
	std::vector<size_t> coordinates_of_cars_to_update;
	std::priority_queue<std::pair<size_t, size_t>> cars_to_update;
};