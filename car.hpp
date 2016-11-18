#pragma once

#include <vector>
#include <memory>

class Side;

class Car
{
public:
	Car() = default;
	Car(size_t coordinate);
	Car(std::vector< std::shared_ptr<Side> > const& path);
	Car(Car const& car);
	~Car() = default;

	Car& operator=(Car const& copied);

	void update(size_t nearest_barrier, 
		size_t nearest_barrier_speed,
		size_t update_frequency,
		size_t recommended_speed,
		size_t safe_distance);

	size_t get_speed() const;
	size_t get_size() const;
	size_t get_coordinate() const;

	std::shared_ptr<Side> where_to_go() const;
	void go();

	std::vector< std::shared_ptr<Side> > path;
private:
	constexpr static size_t critical_distance = 1;
	const size_t car_size = 5;


	size_t coordinate;
	size_t speed; // in metres per second
};