#pragma once
#include "car.hpp"

class Side
{
public:
	void update();
	void print() const;

	void virtual add_to_lane(Car const& car, size_t lane_number = 0) = 0;
};