#pragma once

#include <vector>
#include <memory>

#include "icross_road.hpp"
#include "side.hpp"

class Car_generator : public ICross_road
{
public:
	Car_generator() = default;
	Car_generator(std::shared_ptr<Side> outgoing_side);
	Car_generator(std::shared_ptr<Side> outgoing_side, const std::vector< std::shared_ptr<Side> >& path);

	void update() override;
	bool can_go(std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side) override;
	void go(std::unique_ptr<Car>&& car, std::shared_ptr<Lane> original_lane, std::shared_ptr<Side> new_side) override;

private:
	std::shared_ptr<Side> outgoing_side;
	std::vector< std::shared_ptr<Side> > path;
};