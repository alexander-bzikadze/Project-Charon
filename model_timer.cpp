#include "model_timer.hpp"

using namespace std;

Model_timer::Model_timer(shared_ptr<Model> model, 
	shared_ptr<Model_printer> model_printer, 
	shared_ptr<Model_visualisation> model_visualisation) :
	timer()
{
	connect(&timer, SIGNAL(timeout()), model.get(), SLOT(update()));
	connect(&timer, SIGNAL(timeout()), model_printer.get(), SLOT(print_cars()));
	connect(model_visualisation.get(), SIGNAL(change_activity()), this, SLOT(change_activity()));
}

void Model_timer::change_activity()
{
	if (!timer.isActive())
	{
		timer.start(interval);
	}
	else
	{
		timer.stop();
	}
}