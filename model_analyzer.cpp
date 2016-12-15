#include "model_analyzer.hpp"
#include "model.hpp"

Model_analyzer::Model_analyzer(Model* model) :
	model(model) ,
	metres_in_model(count_metres_in_model(model))
{
}

void Model_analyzer::update()
{
	uint64_t cars_in_sides = 0;
	double sum_speed = 0;
	double cars_per_metre = 0;
	for (auto side : model->get_sides())
	{
		double sum_speed_in_side = 0;
		for (auto lane : side->get_lanes())
		{
			double sum_speed_in_lane = 0;
			cars_in_sides += lane->get_cars().size();
			cars_per_metre += (double)lane->get_cars().size() / side->get_road_length();
			for (auto& car : lane->get_cars())
			{
				sum_speed_in_lane += car->get_speed();
			}
			sum_speed_in_lane /= lane->get_cars().size();
			sum_speed_in_side += sum_speed_in_lane;
		}
		sum_speed_in_side /= side->get_lanes().size();
		sum_speed += sum_speed_in_side;
	}
	sum_speed /= model->get_sides().size();
	push_to_queue(average_speed_queue, sum_speed);
	push_to_queue(cars_per_metre_queue, cars_per_metre);
	uint64_t cars_in_cross_roads = 0;
	for (auto cross_road : model->get_cross_roads())
	{
		cars_in_cross_roads += cross_road->get_cars_in_cross_road().size();
	}
	push_to_queue(car_number_queue, cars_in_sides + cars_in_cross_roads);
	push_to_queue(cars_through_cross_roads_queue, cars_in_cross_roads);
}

template<class T, size_t size>
void Model_analyzer::push_to_queue(PCqueue<T, size>& queue, T pushed)
{
	queue.push_front(pushed);
	if (queue.element_number() == size_of_queue)
	{
		queue.pop_back();
	}
}

uint64_t Model_analyzer::count_metres_in_model(Model* model)
{
	uint64_t sum_of_metres = 0;
	for (auto side : model->get_sides())
	{
		sum_of_metres += side->get_road_length() * side->get_lanes().size();
	}
	return sum_of_metres;
}

double Model_analyzer::current_average_speed() const
{
	return average_speed_queue.top_front();
}

uint64_t Model_analyzer::current_car_number() const
{
	return car_number_queue.top_front();
}

double Model_analyzer::current_cars_per_metre() const
{
	return cars_per_metre_queue.top_front();
}

uint64_t Model_analyzer::current_cars_throigh_cross_roads() const
{
	return cars_through_cross_roads_queue.top_front();
}

double Model_analyzer::average_average_speed() const
{
	return (double)average_speed_queue.sum() / average_speed_queue.element_number();
}

double Model_analyzer::average_car_number() const
{
	return (double)car_number_queue.sum() / car_number_queue.element_number();
}

double Model_analyzer::average_cars_per_metre() const
{
	return (double)cars_per_metre_queue.sum() / cars_per_metre_queue.element_number();
}

double Model_analyzer::average_cars_through_cross_roads() const
{
	return (double)cars_through_cross_roads_queue.sum() / cars_through_cross_roads_queue.element_number();
}

