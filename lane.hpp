#pragma once

#include <vector>

#include "car.hpp"

class Lane
{
public:
	Lane() = default;

	std::vector< std::unique_ptr<Car> > const& get_cars() const;

	void update_car(size_t road_length, 
		size_t const recommended_speed, 
		size_t const safe_distance,
		size_t const index);
	void add_car(std::unique_ptr<Car>&& car);
	Car* go_car(size_t road_length);

	void update();

private:
	std::vector< std::unique_ptr<Car> > cars;
	size_t number_of_cars_to_delete = 0;
};