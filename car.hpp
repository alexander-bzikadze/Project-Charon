#pragma once

#include <vector>
#include <memory>

class Side;

/// Basic class in the model.
/// Holds its coordinate, speed, supposed path of sides and size.
/// Can update its coordinate and speed, answer where to go next, and simulate appearing in a new lane.
class Car
{
public:
	/// Default Car constructor.
	Car() = default;

	/// Constructor with specified initial coordinate.
	Car(size_t coordinate);

	/// Constructor with specified path. Path is used by the car to answer where_to_go method.
	Car(std::vector< std::shared_ptr<Side> > const& path);

	/// Copy-constructor.
	Car(Car const& car);

	/// Default destructor.
	~Car() = default;

	/// = Operator.
	Car& operator=(Car const& copied);

	/// Changes current coordinate of the car depending on neareast barrier coordinate, 
	/// nearest barrier speed, update frequency, recommended speed and safe distance.
	void update(size_t nearest_barrier, 
		size_t nearest_barrier_speed,
		size_t update_frequency,
		size_t recommended_speed,
		size_t safe_distance);

	/// Returns car's current speed.
	size_t get_speed() const;

	/// Returns car's size.
	size_t get_size() const;

	/// Returns car's current coordinate.
	size_t get_coordinate() const;

	/// Returns last Side in path. Is used to get next side, where current car is supposed to go.
	std::shared_ptr<Side> where_to_go() const;

	/// Simulates appearing in a new lane. Pops last element in path and sets coordinate to 0.
	void go();

private:
	constexpr static size_t critical_distance = 1;
	const size_t car_size = 5;

	std::vector< std::shared_ptr<Side> > path;

	size_t coordinate;
	size_t speed; // in metres per second
};