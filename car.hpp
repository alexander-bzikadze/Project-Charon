#pragma once

class Car
{
public:
	Car() = default;

	size_t update(size_t nearest_barrier, 
		size_t nearest_barrier_speed,
		size_t update_frequency,
		size_t recommended_speed,
		size_t safe_distance);

	size_t get_speed() const;
	size_t get_size() const;
	size_t get_coordinate() const;

private:
	constexpr static size_t critical_distance = 1;
	const size_t car_size = 5;

	size_t coordinate;
	size_t speed; // in metres per second
};