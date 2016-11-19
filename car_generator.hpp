#pragma once

#include <vector>
#include <memory>

#include "icross_road.hpp"
#include "side.hpp"

/// Generates cars and pushes them to definite side called outgoing.
class Car_generator
{
public:
	/// Default constructor.
	Car_generator() = default;

	/// Constructor with specified outgoing side.
	Car_generator(std::shared_ptr<Side> outgoing_side);

	/// Constructor that specifies outgoing side and path for cars to be generated.
	Car_generator(std::shared_ptr<Side> outgoing_side, const std::vector< std::shared_ptr<Side> >& path);

	/// Updates itself. Generates one car and pushes it to outgoing side.
	void update();

private:
	std::shared_ptr<Side> outgoing_side = nullptr;
	std::shared_ptr<std::vector< std::shared_ptr<Side> >> path;
};