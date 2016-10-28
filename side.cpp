#include <iostream>
#include <queue>
#include <cmath>

#include "side.hpp"

Side::Side(size_t road_length, size_t lane_number) :
	lanes(lane_number),
	road_length(road_length), 
	recommended_speed(20),
	safe_distance(20)
	{}

Side::Side(size_t road_length, size_t lane_number, 
		size_t recommended_speed, size_t safe_distance) :
	lanes(lane_number),
	road_length(road_length), 
	recommended_speed(recommended_speed),
	safe_distance(safe_distance)
	{}

void Side::update()
{
	size_t *coordinates_of_cars_to_update = new size_t[lanes.size()]();
	std::priority_queue<std::pair<size_t, size_t>> cars_to_update;
	for (size_t i = 0; i < lanes.size(); ++i)
	{
		if (lanes[i].get_cars().size())
			cars_to_update.push({lanes[i].get_cars()[0].get_coordinate(), i});
	}
	while (!cars_to_update.empty())
	{
		auto first_car_coordinates = cars_to_update.top();
		cars_to_update.pop();
		size_t lane_index = first_car_coordinates.second;
		lanes[lane_index].update_car(road_length, recommended_speed, safe_distance, 
								coordinates_of_cars_to_update[lane_index]);
		coordinates_of_cars_to_update[lane_index]++;
		if (coordinates_of_cars_to_update[lane_index] != lanes[lane_index].get_cars().size())
		{
			cars_to_update.push({lanes[lane_index].get_cars()[coordinates_of_cars_to_update[lane_index]].get_coordinate(), lane_index});
		}
	}
	delete[] coordinates_of_cars_to_update;
}

void Side::print() const
{
	size_t max_number_of_cars_in_lane = lanes[0].get_cars().size();
	for (size_t i = 1; i < lanes.size(); ++i)
	{
		max_number_of_cars_in_lane = std::max(max_number_of_cars_in_lane, lanes[i].get_cars().size());
	}
	for (size_t i = 0; i < max_number_of_cars_in_lane; ++i)
	{
		for (size_t j = 0; j < lanes.size(); ++j)
		{
			if (i < lanes[j].get_cars().size())
			{
				std::cout << lanes[j].get_cars()[i].get_coordinate() << " ";
			}
			else
			{
				std::cout << "_ ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool Side::can_add_to_lane(size_t lane_number) const
{
	return !lanes[lane_number].get_cars().size() ||
		 !(lanes[lane_number].get_cars()[lanes[lane_number].get_cars().size() - 1].get_coordinate()
		 < lanes[lane_number].get_cars()[lanes[lane_number].get_cars().size() - 1].get_size() + 1);
}

void Side::add_to_lane(Car const& car, size_t lane_number)
{
	lane_number = std::min(lane_number, lanes.size() - 1);
	lanes[lane_number].add_car(car);
}

bool Side::can_switch_lanes(size_t lane_number, size_t car_number, size_t new_lane_number) const
{
// 	if (abs(lane_number - new_lane_number) != 1)
// 	{
// 		return false;
// 	}
// auto 
// 	if (lanes[lane_number].get_cars()[car_number])
	return true;
}