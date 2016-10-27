#include "lane.hpp"
#include "side.hpp"
#include "one_lane_side.hpp"

int main()
{
	auto r = One_lane_side(1000);
	for (int i = 0; i < 10; ++i)
	{
		r.add_to_lane(Car(), 0);
		r.update();
		r.print();
	}
	r.print();
	for (int i = 0; i < 100; ++i)
	{
		r.update();
		r.print();
	}
	return 0;
}