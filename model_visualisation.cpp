#include "model_visualisation.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsRectItem>
#include <QImage>
#include <QPainter>

using namespace std;
#include <iostream>

Model_visualisation::Model_visualisation(QWidget *parent) :
	QWidget(parent) ,
	mScene(0, 0, 500, 350)
{
	mScene.setBackgroundBrush(Qt::white);

	mView = new QGraphicsView(&mScene, this);
	const auto layout = new QGridLayout(this);
	layout->addWidget(mView, 0, 0, 1, 3);

	crossroad_button = new QPushButton("Add Crossroads");
	road_button = new QPushButton("Add roads");
	start_button = new QPushButton("Start");

	road_button->setEnabled(false);
	start_button->setEnabled(false);

	layout->addWidget(crossroad_button, 1, 0);
	layout->addWidget(road_button, 1, 1);
	layout->addWidget(start_button, 1, 2);

	connect(crossroad_button, SIGNAL(clicked()), this, SLOT(emit_add_crossroads()));
	connect(road_button, SIGNAL(clicked()), this, SLOT(emit_add_sides()));
	connect(start_button, SIGNAL(clicked()), this, SLOT(emit_change_activity()));
	connect(start_button, SIGNAL(clicked()), this, SLOT(change_start_text()));
}

QGraphicsItem* Model_visualisation::add_line(QPointF const& p1, QPointF const& p2, qreal circle_size)
{
	const auto origin_point = p1 + QPointF(circle_size / 2, circle_size / 2);
	const auto dest_point = p2 + QPointF(circle_size / 2, circle_size / 2);
	const auto line = mScene.addLine(origin_point.x(), origin_point.y(), dest_point.x(), dest_point.y());
	return line;
}

QGraphicsItem* Model_visualisation::add_circle(qreal circle_size, QColor color)
{
	const auto circle = mScene.addEllipse(0, 0, circle_size, circle_size, color);
	circle->setFlag(QGraphicsItem::ItemIsMovable);
	circle->setFlag(QGraphicsItem::ItemIsSelectable);
	return circle;
}

void Model_visualisation::fix_item(QGraphicsItem* item)
{
	item->setFlag(QGraphicsItem::ItemIsMovable, false);
	item->setFlag(QGraphicsItem::ItemIsSelectable, false);
}

void Model_visualisation::move_item(QGraphicsItem* item, QPointF const& new_point)
{
	item->setPos(new_point);
}

void Model_visualisation::delete_item(QGraphicsItem* item)
{
	mScene.removeItem(item);
	delete item;
}

void Model_visualisation::emit_add_crossroads()
{
	emit add_crossroads();
}

void Model_visualisation::emit_add_sides()
{
	emit add_sides();
}

void Model_visualisation::emit_change_activity()
{
	emit change_activity();
}

void Model_visualisation::enable_crossroad_button()
{
	crossroad_button->setEnabled(true);
}

void Model_visualisation::enable_road_button()
{
	road_button->setEnabled(true);
}

void Model_visualisation::enable_start_button()
{
	start_button->setEnabled(true);
}

void Model_visualisation::disable_crossroad_button()
{
	crossroad_button->setEnabled(false);
}

void Model_visualisation::disable_road_button()
{
	road_button->setEnabled(false);
}

void Model_visualisation::disable_start_button()
{
	start_button->setEnabled(false);
}

void Model_visualisation::change_start_text()
{
	if (start_button->text() != "Start")
	{
		start_button->setText("Start");
	}
	else
	{
		start_button->setText("Stop");
	}
}

