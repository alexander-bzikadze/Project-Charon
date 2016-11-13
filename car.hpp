#pragma once

#include <vector>

class Side;

class Car
{
public:
	Car() = default;
	Car(size_t coordinate);
	Car(std::vector<Side*> const& path);
	Car(Car const& car);
	~Car() = default;

	void update(size_t nearest_barrier, 
		size_t nearest_barrier_speed,
		size_t update_frequency,
		size_t recommended_speed,
		size_t safe_distance);

	size_t get_speed() const;
	size_t get_size() const;
	size_t get_coordinate() const;

	Side* where_to_go() const;
	void go();

private:
	constexpr static size_t critical_distance = 1;
	const size_t car_size = 5;

	std::vector<Side*> path;

	size_t coordinate;
	size_t speed; // in metres per second
};