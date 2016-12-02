#pragma once

#include <memory>
#include <unordered_map>
#include <QGraphicsItem>

#include "model_visualisation.hpp"
#include "side.hpp"
#include "cross_road.hpp"
#include "car_generator.hpp"
#include "car_degenerator.hpp"

class Model_printer : public QObject
{
	Q_OBJECT
public:
	Model_printer(std::shared_ptr<Model_visualisation> model_visualisation,
				  std::vector< std::shared_ptr<Car_generator> >& car_generators,
				  std::vector< std::shared_ptr<Cross_road> >& cross_roads,
				  std::vector< std::shared_ptr<Car_degenerator> >& car_degenerators);


public slots:
	void add_all_generators_and_cross_roads();
	void add_all_sides();
	void print_cars();


private:
	constexpr static qreal cross_road_size = 50;
	constexpr static qreal car_size = 10;

	void print_side(std::shared_ptr<Side> printed_side, std::shared_ptr<IModel_Object> origin);
	void move_car(std::shared_ptr<Side> printed_side, std::shared_ptr<IModel_Object> origin, size_t car_coordinate, QGraphicsItem* item);

	std::shared_ptr<Model_visualisation> model_visualisation;

	std::vector< std::shared_ptr<Car_generator> >& car_generators;
	std::vector< std::shared_ptr<Cross_road> >& cross_roads;
	std::vector< std::shared_ptr<Car_degenerator> >& car_degenerators;

	std::unordered_map<IModel_Object*, QGraphicsItem*> object_and_their_view;
	std::unordered_map< size_t, QGraphicsItem* > cars_view;
};