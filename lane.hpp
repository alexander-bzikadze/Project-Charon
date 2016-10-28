#pragma once

#include <vector>

#include "car.hpp"

class Lane
{
public:
	Lane() = default;

	std::vector<Car> const& get_cars() const;

	void update_car(size_t road_length, 
		size_t const recommended_speed, 
		size_t const safe_distance,
		size_t const index);
	void add_car(Car const &car);

private:
	std::vector<Car> cars;
};