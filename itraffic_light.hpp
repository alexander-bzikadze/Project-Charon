#pragma once

class Lane;

class ITraffic_light
{
public:
	virtual ~ITraffic_light() = default;
	enum class Availiable_lights : std::uint8_t { main_road, secondary_road, stop_road };
	virtual std::vector< std::pair <std::shared_ptr<Lane>, std::shared_ptr<Lane>>> get_main_roads() = 0;
	virtual	std::vector< std::pair <std::shared_ptr<Lane>, std::shared_ptr<Lane>>> get_active_roads() = 0;
	virtual Availiable_lights get_status(std::shared_ptr<Lane> const original_lane, std::shared_ptr<Lane> const new_lane) = 0;
	virtual void update() = 0;
};