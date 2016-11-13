#include "lane.hpp"
#include "side.hpp"
#include "cross_road.hpp"

#include <iostream>

using namespace std;

void t1(), t2();

int main()
{
	vector<Side*> s;
	for (int i = 0; i < 8; ++i)
	{
		s.push_back(new Side(200, 2));
	}
	Cross_road c(3);
	c.standard_build(s);
	for (int i = 0; i < 8; i+=2)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 8; ++k)
			{
				cout << i << " " << j << " " << k << endl;
				cout << c.can_go(&s[i]->get_lanes()[j], s[k]) << endl;
			}
		}
	}
	return 0;
}

void t1()
{
	auto r = Side(1000, 4);
	std::vector<Car*> v;
	auto p = new Car();
	v.push_back(p);
	r.add_to_lane(p, 0);
	r.update();
	// r.print();
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 4; ++j)
		if (r.can_add_to_lane(j)){
			v.push_back(new Car());
			r.add_to_lane(v[v.size()-1], j);
		}
		// r.print();
		r.update();
	}
	// auto p = r.get_car(3, 3);
	for (int i = 0; i < v.size(); ++i)
	{
		// cout << v[i]->get_coordinate() << " ";
	}
	for (int i = 0; i < 20; ++i)
	{
		r.update();
		// r.print();
	}
	// r.print();
}