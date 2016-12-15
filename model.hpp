#pragma once

#include <vector>
#include <memory>

#include "side.hpp"
#include "cross_road.hpp"
#include "car_generator.hpp"
#include "car_degenerator.hpp"

#include <QObject>

/// Describes model. Its inner parts are builded outside, then given to Model constructor.
/// Models objective is to update their status.
class Model : public QObject
{
	Q_OBJECT
public:
	Model(std::vector< std::shared_ptr<Side> >& sides,
		  std::vector< std::shared_ptr<Car_generator> >& car_generators,
		  std::vector< std::shared_ptr<Cross_road> >& cross_roads,
		  std::vector< std::shared_ptr<Car_degenerator> >& car_degenerators);

	std::vector< std::shared_ptr<Side> > const& get_sides() const;
	std::vector< std::shared_ptr<Car_generator> > const& get_car_generators() const;
	std::vector< std::shared_ptr<Cross_road> > const& get_cross_roads() const;
	std::vector< std::shared_ptr<Car_degenerator> > const& get_car_degenerators() const;

	void call_event_car_added(Car* car_pointer);

signals:
	void event_car_added(Car* car);

public slots:
	void update();

private:
	std::vector< std::shared_ptr<Side> >& sides;
	std::vector< std::shared_ptr<Car_generator> >& car_generators;
	std::vector< std::shared_ptr<Cross_road> >& cross_roads;
	std::vector< std::shared_ptr<Car_degenerator> >& car_degenerators;

	uint64_t current_number_of_cars = 0;
	uint64_t sum_of_cars_in_period = 0;
};