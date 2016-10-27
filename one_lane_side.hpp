#pragma once
#include "side.hpp"
#include "lane.hpp"

class One_lane_side : public Side
{
public:
	One_lane_side() = default;

	One_lane_side(int road_length) : 
		lane(road_length)
		{}

	void update();
	void print() const;

	void add_to_lane(Car const& car, size_t lane_number);

private:
	Lane lane;

	static constexpr int recommended_speed = 20;
	static constexpr int safe_distance = 20;
};