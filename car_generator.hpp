#pragma once

#include <vector>

#include "icross_road.hpp"
#include "side.hpp"

class Car_generator : public ICross_road
{
public:
	Car_generator() = default;
	Car_generator(Side* outgoing_side, std::vector<Side*> path);

	void update() override;
	bool can_go(Lane* const original_lane, Side* const new_side) override;
	void go(Car* car, Lane* original_lane, Side* const new_side) override;

private:
	Side* outgoing_side;
	std::vector<Side*> path;
};