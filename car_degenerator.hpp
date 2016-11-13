#pragma once

#include <vector>

#include "icross_road.hpp"
#include "side.hpp"

class Car_degenerator : public ICross_road
{
public:
	Car_degenerator() = default;

	void update() override;
	bool can_go(Lane* const original_lane, Side* const new_side) override;
	void go(Car* car, Lane* original_lane, Side* const new_side) override;

private:
	std::vector<Car*> cars_to_delete;
};