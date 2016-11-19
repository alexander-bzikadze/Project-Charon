#pragma once

#include "car.hpp"

class Lane;
class Side;

/// Interface of a cross_road. Can be updated, asked, 
/// if car can cross it, and forced to be crossed by car.
class ICross_road
{
public:
	// virtual ~ICross_road();

	/// Updates status in abstract cross_road.
	virtual void update() = 0;

	/// Answers, if icross_road can be crossed.
	virtual bool can_go(std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side) = 0;

	/// Forced to be crossed by a car.
	virtual void go(std::unique_ptr<Car>&& car, std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side) = 0;
};