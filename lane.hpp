#pragma once

#include <vector>

#include "car.hpp"

/// A class to hold cars.
/// General meaning is simple road lane.
/// Can return const vector of unique_ptrs on Car, update car by index, add car, move car, update itself.
class Lane
{
public:
	/// Default constructor.
	Lane() = default;

	/// Return by const reference all holded cars.
	std::vector< std::unique_ptr<Car> > const& get_cars() const;

	/// Updates chosen by index car.
	void update_car(size_t road_length, 
		size_t const recommended_speed, 
		size_t const safe_distance,
		size_t const index);

	/// Adds car to the end of the cars vector.
	void add_car(std::unique_ptr<Car>&& car);

	/// Releases pointer to went Car from unique_ptr and returns it. 
	/// Warning! This pointer is supposed to be caught into unique_ptr immediately.
	Car* go_car(size_t road_length);

	/// Updates cars vector - deletes all gone cars.
	void update();

private:
	std::vector< std::unique_ptr<Car> > cars;
	size_t number_of_cars_to_delete = 0;
};