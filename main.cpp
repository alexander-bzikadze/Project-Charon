#include "lane.hpp"
#include "side.hpp"
#include "cross_road.hpp"
#include "car_generator.hpp"
#include "car_degenerator.hpp"

#include <iostream>

using namespace std;

void t1(), t2(), t3();

int main()
{
	t1();
	t2();
	t3();


	return 0;
}

void t3()
{
	Side* s = new Side(100, 1);
	std::vector<Side*> path;
	path.push_back(nullptr);
	Car_generator p = Car_generator(s, path);
	Car_degenerator q = Car_degenerator();
	s->build(&q);
	for (int i = 0; i < 10; ++i)
	{
		p.update();
		s->update();
		cout << "!" << endl;
		q.update();
		s->print();
	}
}

void t2()
{
	vector<Side*> s;
	for (int i = 0; i < 8; ++i)
	{
		s.push_back(new Side(200, 1));
	}
	Cross_road c(3);
	c.standard_build(s);
	for (int i = 0; i < 8; i+=2)
	{
		for (int j = 0; j < 1; ++j)
		{
			for (int k = 0; k < 8; ++k)
			{
				// cout << i << " " << j << " " << k << endl;
				// cout << c.can_go(&s[i]->get_lanes()[j], s[k]) << endl;
			}
		}
	}
}

void t1()
{
	auto r = Side(200, 4);
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