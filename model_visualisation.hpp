#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>

class Model_visualisation : public QWidget
{
	Q_OBJECT
public:
	Model_visualisation(QWidget *parent = 0);
	~Model_visualisation() = default;

	QGraphicsItem* add_line(QPointF const& p1, QPointF const& p2, qreal circle_size);
	QGraphicsItem* add_circle(qreal circe_size, QColor color = Qt::black);

	void fix_item(QGraphicsItem* item);
	void move_item(QGraphicsItem* item, QPointF const& new_point);
	void delete_item(QGraphicsItem* item);

	void enable_crossroad_button();
	void enable_road_button();
	void enable_start_button();
	void disable_crossroad_button();
	void disable_road_button();
	void disable_start_button();

signals:
	void add_crossroads();
	void add_sides();
	void change_activity();

private:
	QGraphicsScene mScene;
	QGraphicsView *mView;
	QPushButton* crossroad_button;
	QPushButton* road_button;
	QPushButton* start_button;

private slots:
	void emit_add_crossroads();
	void emit_add_sides();
	void emit_change_activity();
	void change_start_text();
};