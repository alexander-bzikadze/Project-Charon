#include "lane.hpp"
#include "side.hpp"

#include <iostream>

using namespace std;

int main()
{
	auto r = Side(1000, 4);
	r.add_to_lane(Car(), 0);
	r.update();
	r.print();
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 4; ++j)
		if (r.can_add_to_lane(j)){
			auto c1 = Car();
			r.add_to_lane(c1, j);
		}
		r.print();
		r.update();
	}
	// auto p = r.get_car(3, 3);
	for (int i = 0; i < 20; ++i)
	{
		r.update();
		// r.print();
	}
	r.print();
	// cout << r.can_switch_lanes(1, 3, 2) << endl;
	return 0;
}