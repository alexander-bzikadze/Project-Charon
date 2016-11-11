#include <vector>
#include <unordered_map>
#include <cstdint>

#include "cross_road.hpp"

using namespace std;

Cross_road::Standard_builder::Standard_builder(Cross_road* builded) :
	builded(builded)
	{}

void Cross_road::Standard_builder::build(vector<Side*> sides)
{
	if (sides.size() != expected)
	{
		//throw something
	}
	for (size_t i = 1; i < sides.size(); ++i)
	{
		if (sides[i]->get_lanes().size() != sides[i - 1]->get_lanes().size())
		{
			//throw something
		}
	}
	size_t max_status = 2;
	std::vector <std::unordered_map <Lane*, std::unordered_map <Lane*, size_t>>> road_status;
	road_status.resize(max_status);
	for (size_t i = 0; i < expected; i += 2)
	{
		size_t current_road_status = (i % 4) / 2;
		size_t anti_current_road_status = ((i % 4) / 2 + 1) % 2;
		auto left = &sides[i]->get_lanes()[0];
		auto right = &sides[i]->get_lanes()[sides[i]->get_lanes().size() - 1];
		auto destination_of_left = &sides[(i + 5) % expected]->get_lanes()[0];
		auto destination_of_right = &sides[(i + 3) % expected]->get_lanes()[sides[i]->get_lanes().size() - 1];
		// road_status[0][left]
		builded->lane_connections[left][sides[(i + 5) % expected]] = destination_of_left;
		builded->lane_connections[right][sides[(i + 3) % expected]] = destination_of_right;
		road_status[current_road_status][left][destination_of_left] = 1;
		road_status[current_road_status][right][destination_of_right] = 1;
		road_status[anti_current_road_status][left][destination_of_left] = 2;
		road_status[anti_current_road_status][right][destination_of_right] = 2;
		for (size_t j = 0; j < sides[i]->get_lanes().size(); ++j)
		{
			auto current_lane = &sides[i]->get_lanes()[j];
			auto current_lane_destination = &sides[(i + 4) & expected]->get_lanes()[j];
			builded->lane_connections[current_lane][sides[(i + 4) & expected]] = current_lane_destination;
			road_status[current_road_status][current_lane][current_lane_destination] = 0;
			road_status[anti_current_road_status][current_lane][current_lane_destination] = 2;
		}
	}
	size_t added_lanes = 0;
	for (size_t i = 0; i < expected; ++i)
	{
		for (size_t j = 0; j < sides[i]->get_lanes().size(); ++j)
		{
			builded->number_of_lanes_in_clock_order[&sides[i]->get_lanes()[j]] = added_lanes++;
		}
	}
	builded->traffic_light = Traffic_light(max_status, road_status);
}