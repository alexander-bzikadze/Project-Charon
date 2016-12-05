#include "side.hpp"
#include "cross_road.hpp"
#include "car_generator.hpp"
#include "car_degenerator.hpp"
#include "model_visualisation.hpp"
#include "model_printer.hpp"
#include "model_timer.hpp"

#include <iostream>
#include <QApplication>

using namespace std;

void t1(), t2(), t3(), t4(),  t5();
int t6(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	// t1();
	// t2();
	// t3();
	// t4();
	// t5();
	return t6(argc, argv);
}

int t6(int argc, char* argv[])
{
	vector< shared_ptr<Car_generator> > cg(4);
	vector< shared_ptr<Cross_road> > cr(1);
	vector< shared_ptr<Side> > s(8);
	vector< shared_ptr<Car_degenerator> > cd(4);
	for (int i = 0; i < s.size(); ++i)
	{
		s[i] = shared_ptr<Side>(new Side(3000, 1));
	}
	for (int i = 0; i < cg.size(); ++i)
	{
		cg[i] = shared_ptr<Car_generator>(new Car_generator(s[i], {nullptr, s[i + 4]}));
		cd[i] = shared_ptr<Car_degenerator>(new Car_degenerator());
		s[i + 4]->build(cd[i].get());
	}
	cr[0] = shared_ptr<Cross_road>(new Cross_road(3));
	cr[0]->standard_build({s[0], s[4], s[1], s[5], s[2], s[6], s[3], s[7]});
	QApplication a(argc, argv);
	shared_ptr<Model_visualisation> w(new Model_visualisation());
	w->show();
	shared_ptr<Model> md(new Model(s,cg,cr,cd));
	shared_ptr<Model_printer> mp(new Model_printer(w, md));
	shared_ptr<Model_timer> mt(new Model_timer(md, mp, w));
	return a.exec();
}

void t5()
{
	vector< shared_ptr<Car_generator> > cg(4);
	vector< shared_ptr<Cross_road> > cr(1);
	vector< shared_ptr<Side> > s(8);
	vector< shared_ptr<Car_degenerator> > cd(4);
	for (int i = 0; i < s.size(); ++i)
	{
		s[i] = shared_ptr<Side>(new Side(100, 1));
	}
	for (int i = 0; i < cg.size(); ++i)
	{
		cg[i] = shared_ptr<Car_generator>(new Car_generator(s[i], {nullptr, s[i + 4]}));
		cd[i] = shared_ptr<Car_degenerator>(new Car_degenerator());
		s[i + 4]->build(cd[i].get());
	}
	cr[0] = shared_ptr<Cross_road>(new Cross_road(3));
	cr[0]->standard_build({s[0], s[4], s[1], s[5], s[2], s[6], s[3], s[7]});
	for (int j = 0; j < 1000; ++j)
	{
		for (int i = 0; i < cg.size(); ++i)
			cg[i]->update();
		for (int i = 0; i < s.size(); ++i)
			s[i]->update();
		for (int i = 0; i < cr.size(); ++i)
			cr[i]->update();
		for (int i = 0; i < cd.size(); ++i)
			cd[i]->update();
		// s[2]->print();
	}
}

void t4()
{
	vector< shared_ptr<Car_generator> > cg(6);
	vector< shared_ptr<Car_degenerator> > cd(6);
	vector< shared_ptr<Cross_road> > cr(2);
	vector< shared_ptr<Side> > s(14);
	for (int i = 0; i < 14; ++i)
	{
		s[i] = shared_ptr<Side>(new Side(30, 1));
	}
	vector< shared_ptr<Side> > path1 = {nullptr, s[12], s[0]};
	vector< shared_ptr<Side> > path2 = {nullptr, s[12], s[1]};
	for (int i = 0; i < 3; ++i)
	{
		cg[i] = shared_ptr<Car_generator>(new Car_generator(s[i + 2], path1));
		cd[i] = shared_ptr<Car_degenerator>(new Car_degenerator());
		s[i + 8]->build(cd[i].get());
	}
	for (int i = 3; i < 6; ++i)
	{
		cg[i] = shared_ptr<Car_generator>(new Car_generator(s[i + 2], path2));
		cd[i] = shared_ptr<Car_degenerator>(new Car_degenerator());
		s[i + 8]->build(cd[i].get());
	}
	for (int i = 0; i < 2; ++i)
	{
		cr[i] = shared_ptr<Cross_road>(new Cross_road(3));
	}
	cr[0]->standard_build({s[2], s[9], s[3], s[10], s[4], s[0], s[1], s[8]});
	cr[1]->standard_build({s[5], s[12], s[6], s[3], s[7], s[1], s[0], s[11]});
	for (int j = 0; j < 180; ++j)
	{
		for (int i = 0; i < cg.size(); ++i)
			cg[i]->update();
		for (int i = 0; i < s.size(); ++i)
			s[i]->update();
		for (int i = 0; i < cr.size(); ++i)
			cr[i]->update();
		for (int i = 0; i < cd.size(); ++i)
			cd[i]->update();
		// s[3]->print();
	}
}

void t3()
{
	shared_ptr<Side> s(new Side(100, 1));
	std::vector<shared_ptr<Side>> path;
	path.push_back(nullptr);
	Car_generator p(s, path);
	shared_ptr<Car_degenerator> q(new Car_degenerator());
	s->build(q.get());
	for (int i = 0; i < 180; ++i)
	{
		p.update();
		// s->print();
		s->update();
		q->update();
	}
}

void t2(vector<shared_ptr<Side>>& s)
{
	Cross_road c(3);
	c.standard_build(s);
	for (int i = 0; i < 8; i+=2)
	{
		for (int j = 0; j < 1; ++j)
		{
			for (int k = 0; k < 8; ++k)
			{
				// cout << i << " " << j << " " << k << endl;
				// cout << c.can_go(shared_ptr<Lane>(s[i]->get_lanes()[j]), s[k]) << endl;
			}
		}
	}
	c.update();
	for (int i = 0; i < 8; i+=2)
	{
		for (int j = 0; j < 1; ++j)
		{
			for (int k = 0; k < 8; ++k)
			{
				// cout << i << " " << j << " " << k << endl;
				// cout << c.can_go(shared_ptr<Lane>(s[i]->get_lanes()[j]), s[k]) << endl; 
			}
		}
	}
	// cout << "t2" << endl;
}

void t2()
{
	vector<shared_ptr<Side>> s;
	for (int i = 0; i < 8; ++i)
	{
		s.push_back(shared_ptr<Side>(new Side(200, 1)));
	}
	t2(s);
	for (int i = 0; i < s.size(); ++i)
	{
		// cout << s[i].use_count() << " ";
		// cout << s[i]->get_lanes()[0].use_count() << endl;
	}
}

void t1()
{

	auto r = Side(200, 4);
	r.build(nullptr);
	std::vector<Car> v;
	auto p = unique_ptr<Car>(new Car());
	r.add_to_lane(move(p), 0);
	r.update();
	// r.print();
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 4; ++j)
		if (r.can_add_to_lane(j)){
			r.add_to_lane(unique_ptr<Car>(new Car()), j);
		}
		// r.print();
		r.update();
	}
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i].get_coordinate() << " ";
	}
	for (int i = 0; i < 20; ++i)
	{
		r.update();
		// r.print();
	}
	// r.print();
}