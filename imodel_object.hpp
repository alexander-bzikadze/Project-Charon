#pragma once

#include <memory>

class IModel_Object
{
public:
	virtual ~IModel_Object() = default;

	virtual void update() = 0;
	// virtual std::vector<std::shared_ptr<IMo>>
};