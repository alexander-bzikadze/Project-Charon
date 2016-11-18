#pragma once

#include "car.hpp"
#include "lane.hpp"
#include "side.hpp"

class ICross_road
{
public:
	// virtual ~ICross_road();
	virtual void update() = 0;
	virtual bool can_go(std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side) = 0;
	virtual void go(std::unique_ptr<Car>&& car, std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side) = 0;
};