#pragma once

#include <memory>

/// Describes simpiest object of the Model.
class IModel_Object
{
public:
	virtual ~IModel_Object() = default;

	/// Update status of current model object.
	virtual void update() = 0;
};