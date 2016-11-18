#pragma once

#include <vector>
#include <memory>

#include "icross_road.hpp"
#include "side.hpp"

class Car_degenerator : public ICross_road
{
public:
	Car_degenerator() = default;

	void update() override;
	bool can_go(std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side) override;
	void go(std::unique_ptr<Car>&& car, std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side) override;

private:
	std::vector< std::unique_ptr<Car> > cars_to_delete;
};