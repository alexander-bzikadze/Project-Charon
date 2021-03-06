#pragma once

#include <vector>
#include <memory>

#include "imodel_object.hpp"
#include "side.hpp"

/// Generates cars and pushes them to definite side called outgoing.
class Car_generator : public IModel_Object
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

	/// Returns pointer to the side which cars are added to by update().
	std::shared_ptr<Side> const get_outgoing_side() const;

private:
	constexpr static size_t interval = 30;
	size_t current_interval = 0;

	std::shared_ptr<Side> outgoing_side = nullptr;
	std::shared_ptr<std::vector< std::shared_ptr<Side> >> path;
};