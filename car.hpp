#pragma once

class Car
{
public:
	Car() = default;

	int update(int nearest_barrier, 
		int nearest_barrier_speed,
		int update_frequency,
		int recommended_speed,
		int safe_distance);

	int get_speed() const;
	int get_size() const;

private:
	constexpr static int critical_distance = 1;
	const int car_size = 5;

	int speed; // in metres per second
};