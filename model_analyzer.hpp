#pragma once

#include <cstdint>

#include "queue.hpp"

class Model;

class Model_analyzer
{
public:
	Model_analyzer(Model* model);

	double current_average_speed() const;
	uint64_t current_car_number() const;
	double current_cars_per_metre() const;
	uint64_t current_cars_throigh_cross_roads() const;

	double average_average_speed() const;
	double average_car_number() const;
	double average_cars_per_metre() const;
	double average_cars_through_cross_roads() const;

	void update();

private:
	Model* model;
	const uint64_t metres_in_model;

	static uint64_t count_metres_in_model(Model* model);

	template<class T, size_t size>
	void push_to_queue(PCqueue<T, size>& queue, T pushed);

	size_t static constexpr max_size_of_queue = 256;
	size_t static constexpr size_of_queue = 126;

	PCqueue<double, max_size_of_queue> average_speed_queue;
	PCqueue<uint64_t, max_size_of_queue> car_number_queue;
	PCqueue<double, max_size_of_queue> cars_per_metre_queue;
	PCqueue<uint64_t, max_size_of_queue> cars_through_cross_roads_queue;

};