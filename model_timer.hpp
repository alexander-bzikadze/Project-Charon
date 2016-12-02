#pragma once

#include "model.hpp"
#include "model_printer.hpp"

#include <QTimer>

class Model_timer : public QObject
{
	Q_OBJECT
public:
	Model_timer(Model* model, Model_printer* model_printer);

signals:
	void update();

public slots:
	void change_activity();

private:
	constexpr static int interval = 40;

	Model* model;
	Model_printer* model_printer;
	QTimer timer;
};