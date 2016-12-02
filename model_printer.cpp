#include "model_printer.hpp"

#include <QPainter>

using namespace std;

Model_printer::	Model_printer(std::shared_ptr<Model_visualisation> model_visualisation,
				  std::vector< std::shared_ptr<Car_generator> >& car_generators,
				  std::vector< std::shared_ptr<Cross_road> >& cross_roads,
				  std::vector< std::shared_ptr<Car_degenerator> >& car_degenerators) :
				  model_visualisation(model_visualisation) ,
				  car_generators(car_generators) ,
				  cross_roads(cross_roads) ,
				  car_degenerators(car_degenerators)
	{}

void Model_printer::add_all_generators_and_cross_roads()
{
	for (const auto& printed_model_object : car_generators)
	{
		const auto added_graphic_item = model_visualisation->add_circle(cross_road_size, Qt::green);
		object_and_their_view[printed_model_object.get()] = added_graphic_item;
	}
	for (auto const& printed_model_object : cross_roads)
	{
		const auto added_graphic_item = model_visualisation->add_circle(cross_road_size, Qt::cyan);
		object_and_their_view[printed_model_object.get()] = added_graphic_item;
	}
	for (auto const& printed_model_object : car_degenerators)
	{
		const auto added_graphic_item = model_visualisation->add_circle(cross_road_size, Qt::red);
		object_and_their_view[printed_model_object.get()] = added_graphic_item;
	}
}

void Model_printer::print_side(shared_ptr<Side> printed_side, shared_ptr<IModel_Object> origin)
{
	model_visualisation->add_line(object_and_their_view[origin.get()]->pos(), object_and_their_view[printed_side->get_destination()]->pos(), cross_road_size);
}

void Model_printer::move_car(shared_ptr<Side> printed_side, shared_ptr<IModel_Object> origin, size_t car_coordinate, QGraphicsItem* item)
{
	const auto& origin_point = object_and_their_view[origin.get()]->pos();
	const auto& dest_point = object_and_their_view[printed_side->get_destination()]->pos();
	const qreal relation_of_coord_to_side_size = (qreal)printed_side->get_road_length() / (qreal)car_coordinate;
	const auto& new_point = dest_point - relation_of_coord_to_side_size * origin_point;
	model_visualisation->move_item(item, new_point);
}

void Model_printer::add_all_sides()
{
	for (const auto& originator_model_object : car_generators)
	{
		const auto printed_side = originator_model_object->get_outgoing_side();
		print_side(printed_side, originator_model_object);
		model_visualisation->fix_item(object_and_their_view[originator_model_object.get()]);
	}
	for (auto const& originator_model_object : cross_roads)
	{
		for (auto const& printed_side : originator_model_object->get_outgoing_sides())
		{
			print_side(printed_side, originator_model_object);
		}
		model_visualisation->fix_item(object_and_their_view[originator_model_object.get()]);
	}
	for (auto const& originator_model_object : car_degenerators)
	{
		model_visualisation->fix_item(object_and_their_view[originator_model_object.get()]);
	}
}

void Model_printer::print_cars()
{
	for (auto const& degenerator : car_degenerators)
	{
		for (auto const& deleted_car : degenerator->get_cars_to_delete())
		{
			model_visualisation->delete_item(cars_view[hash<unique_ptr<Car>>()(deleted_car)]);
		}
	}	
	for (const auto& generator : car_generators)
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
	for (auto const& cross_road : cross_roads)
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