#pragma once

#include <vector>

#include "car.hpp"

class Lane
{
public:
	Lane() = default;

	std::vector<Car> const& get_cars() const;
	std::vector<size_t> const& get_coordinates() const;

	void update_car(size_t road_length, 
		size_t const recommended_speed, 
		size_t const safe_distance,
		size_t const index);
	void add_car(Car const &car, size_t coordinate = 0);

private:
	std::vector<Car> cars;
	std::vector<size_t> coordinates;
};