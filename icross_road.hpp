#pragma once

#include "car.hpp"
#include "lane.hpp"
#include "side.hpp"

class ICross_road
{
public:
	virtual void update() = 0;
	virtual bool can_go(Lane* const original_lane, Side* const new_side) = 0;
	virtual void go(Car* car, Lane* original_lane, Side* const new_side) = 0;
};