#include "model_printer.hpp"

#include <QPainter>

using namespace std;

Model_printer::	Model_printer(std::shared_ptr<Model_visualisation> model_visualisation,
							shared_ptr<Model> model) :
	model_visualisation(model_visualisation) ,
	model(model)
{
	connect(model_visualisation.get(), SIGNAL(add_crossroads()), this, SLOT(add_all_generators_and_cross_roads()));
	connect(model_visualisation.get(), SIGNAL(add_sides()), this, SLOT(add_all_sides()));
}

void Model_printer::add_all_generators_and_cross_roads()
{
	for (const auto& printed_model_object : model->get_car_generators())
	{
		const auto added_graphic_item = model_visualisation->add_circle(cross_road_size, Qt::green);
		object_and_their_view[printed_model_object.get()] = added_graphic_item;
	}
	for (auto const& printed_model_object : model->get_cross_roads())
	{
		const auto added_graphic_item = model_visualisation->add_circle(cross_road_size, Qt::cyan);
		object_and_their_view[printed_model_object.get()] = added_graphic_item;
	}
	for (auto const& printed_model_object : model->get_car_degenerators())
	{
		const auto added_graphic_item = model_visualisation->add_circle(cross_road_size, Qt::red);
		object_and_their_view[printed_model_object.get()] = added_graphic_item;
	}
	model_visualisation->disable_crossroad_button();
	model_visualisation->enable_road_button();
}

void Model_printer::print_side(shared_ptr<Side> printed_side, shared_ptr<IModel_Object> origin)
{
	model_visualisation->add_line(object_and_their_view[origin.get()]->pos(), object_and_their_view[printed_side->get_destination()]->pos(), cross_road_size);
}

void Model_printer::move_car(shared_ptr<Side> printed_side, shared_ptr<IModel_Object> origin, size_t car_coordinate, QGraphicsItem* item)
{
	const auto& origin_point = object_and_their_view[origin.get()]->pos();
	const auto& dest_point = object_and_their_view[printed_side->get_destination()]->pos();
	const qreal relation_of_coord_to_side_size =  (qreal)car_coordinate / (qreal)printed_side->get_road_length();
	const auto& new_point = (dest_point - origin_point) * relation_of_coord_to_side_size + origin_point + QPointF(cross_road_size / 2, cross_road_size / 2);
	model_visualisation->move_item(item, new_point);
}

void Model_printer::add_all_sides()
{
	for (const auto& originator_model_object : model->get_car_generators())
	{
		const auto printed_side = originator_model_object->get_outgoing_side();
		print_side(printed_side, originator_model_object);
		model_visualisation->fix_item(object_and_their_view[originator_model_object.get()]);
	}
	for (auto const& originator_model_object : model->get_cross_roads())
	{
		for (auto const& printed_side : originator_model_object->get_outgoing_sides())
		{
			print_side(printed_side, originator_model_object);
		}
		model_visualisation->fix_item(object_and_their_view[originator_model_object.get()]);
	}
	for (auto const& originator_model_object : model->get_car_degenerators())
	{
		model_visualisation->fix_item(object_and_their_view[originator_model_object.get()]);
	}
	model_visualisation->disable_road_button();
	model_visualisation->enable_start_button();
}

void Model_printer::print_cars()
{
	for (auto const& degenerator : model->get_car_degenerators())
	{
		for (auto const& deleted_car : degenerator->get_cars_to_delete())
		{
			model_visualisation->delete_item(cars_view[hash<unique_ptr<Car>>()(deleted_car)]);
			cars_view.erase(hash<unique_ptr<Car>>()(deleted_car));
		}
	}	
	for (const auto& generator : model->get_car_generators())
	{
		const auto updated_side = generator->get_outgoing_side();
		for (auto const& updated_lane : updated_side->get_lanes())
		{
			for (auto const& updated_car : updated_lane->get_cars())
			{
				if (cars_view[hash<unique_ptr<Car>>()(updated_car)] == nullptr)
				{
					cars_view[hash<unique_ptr<Car>>()(updated_car)] = model_visualisation->add_circle(car_size);
				}
				move_car(updated_side, generator, updated_car->get_coordinate(), cars_view[hash<unique_ptr<Car>>()(updated_car)]);
			}
		}
	}
	for (auto const& cross_road : model->get_cross_roads())
	{
		for (auto const& updated_side : cross_road->get_outgoing_sides())
		{
			for (auto const& updated_lane : updated_side->get_lanes())
			{
				for (auto const& updated_car : updated_lane->get_cars())
				{
					if (cars_view[hash<unique_ptr<Car>>()(updated_car)] == nullptr)
					{
						cars_view[hash<unique_ptr<Car>>()(updated_car)] = model_visualisation->add_circle(car_size);
					}
					move_car(updated_side, cross_road, updated_car->get_coordinate(), cars_view[hash<unique_ptr<Car>>()(updated_car)]);
				}
			}
		}
	}
}