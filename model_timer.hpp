#pragma once

#include "model.hpp"
#include "model_printer.hpp"
#include "model_visualisation.hpp"

#include <QTimer>

/// Qt object that sends signals model and model_printer to be updated.
class Model_timer : public QObject
{
	Q_OBJECT
public:
	Model_timer(std::shared_ptr<Model> model, 
		std::shared_ptr<Model_printer> model_printer,
		std::shared_ptr<Model_visualisation> model_visualisation);

signals:
	/// Signal to be updated.
	void update();

public slots:
	/// Start or end updating.
	void change_activity();

private:
	constexpr static int interval = 40;

	QTimer timer;
};