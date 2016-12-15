#pragma once

#include <memory>
#include <unordered_map>
#include <QGraphicsItem>

#include "model_visualisation.hpp"
#include "model.hpp"

/// Class that prints Model.
class Model_printer : public QObject
{
	Q_OBJECT
public:
	Model_printer(std::shared_ptr<Model_visualisation> model_visualisation,
				  std::shared_ptr<Model> model);


public slots:
	/// Adds all cross_roads, generators and degenerators to model_visualisation.
	void add_all_generators_and_cross_roads();

	/// Adds all sides between cross_roads, generators and degenerators to model_visualisation.
	void add_all_sides();

	/// Updates cars view in model_visualisation.
	void print_cars();


private:
	constexpr static qreal cross_road_size = 50;
	constexpr static qreal car_size = 10;

	static qreal length(QPointF const& p1, QPointF const& p2);
	static qreal sin(QPointF const& p1, QPointF const& p2);
	static qreal cos(QPointF const& p1, QPointF const& p2);

	void print_side(std::shared_ptr<Side> printed_side, std::shared_ptr<IModel_Object> origin);
	void move_car(std::shared_ptr<Side> printed_side, std::shared_ptr<IModel_Object> origin, size_t car_coordinate, QGraphicsItem* item);

	std::shared_ptr<Model_visualisation> model_visualisation;

	std::shared_ptr<Model> model;

	std::unordered_map<IModel_Object*, QGraphicsItem*> object_and_their_view;
	std::unordered_map< size_t, QGraphicsItem* > cars_view;
};