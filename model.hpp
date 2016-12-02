#pragma once

#include <vector>
#include <memory>

#include "side.hpp"
#include "cross_road.hpp"
#include "car_generator.hpp"
#include "car_degenerator.hpp"

#include <QObject>

class Model : public QObject
{
	Q_OBJECT
public:
	Model(std::vector< std::shared_ptr<Side> >& sides,
		  std::vector< std::shared_ptr<Car_generator> >& car_generators,
		  std::vector< std::shared_ptr<Cross_road> >& cross_roads,
		  std::vector< std::shared_ptr<Car_degenerator> >& car_degenerators);

public slots:
	void update();

private:
	std::vector< std::shared_ptr<Side> >& sides;
	std::vector< std::shared_ptr<Car_generator> >& car_generators;
	std::vector< std::shared_ptr<Cross_road> >& cross_roads;
	std::vector< std::shared_ptr<Car_degenerator> >& car_degenerators;
};