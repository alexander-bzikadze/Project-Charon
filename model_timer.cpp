#include "model_timer.hpp"

Model_timer::Model_timer(Model* model, Model_printer* model_printer) :
	model(model) ,
	model_printer(model_printer) ,
	timer()
{
	connect(&timer, SIGNAL(timeout()), model, SLOT(update()));
	connect(&timer, SIGNAL(timeout()), model_printer, SLOT(print_cars()));
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