#pragma once

#include <vector>
#include <memory>

#include "icross_road.hpp"

class Lane;
class Side;

/// Implementation of ICross_road.
/// Is forced to take cars from sides and to delete them.
class Car_degenerator : public ICross_road
{
public:
	/// Default constructor.
	Car_degenerator() = default;

	/// Deletes taken cars.
	void update() override;

	/// Checks if car is supposed to be destroyed meaning its current next side is nullptr.
	bool can_go(std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side) override;

	/// Takes car to be stored for update frequency time.
	void go(std::unique_ptr<Car>&& car, std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side) override;

	/// Returns cars, that are to be deleted after next update().
	std::vector< std::unique_ptr<Car> > const& get_cars_to_delete();

private:
	std::vector< std::unique_ptr<Car> > cars_to_delete;
};