#include "lane.hpp"
#include "side.hpp"

#include <iostream>

int main()
{
	auto r = Side(1000, 4);
	r.add_to_lane(Car(), 0);
	r.update();
	r.print();
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 4; ++j)
			if (r.can_add_to_lane(j))
				r.add_to_lane(Car(), j);
		r.print();
		r.update();
	}
	for (int i = 0; i < 20; ++i)
	{
		r.update();
		r.print();
	}
	return 0;
}