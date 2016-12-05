#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>

/// Visualisation of the Model with the help of Qt graphic scene.
class Model_visualisation : public QWidget
{
	Q_OBJECT
public:
	Model_visualisation(QWidget *parent = 0);
	~Model_visualisation() = default;

	/// Add line to the scene.
	QGraphicsItem* add_line(QPointF const& p1, QPointF const& p2, qreal circle_size);

	/// Add circle to the scene.
	QGraphicsItem* add_circle(qreal circe_size, QColor color = Qt::black);

	/// Fix all items in the scene besides cars.
	void fix_item(QGraphicsItem* item);

	///Move item by new position.
	void move_item(QGraphicsItem* item, QPointF const& new_point);

	/// Delete item from the scene.
	void delete_item(QGraphicsItem* item);

	/// Enable and disables buttons.
	void enable_crossroad_button();
	void enable_road_button();
	void enable_start_button();
	void disable_crossroad_button();
	void disable_road_button();
	void disable_start_button();

signals:
	/// Adds crossroads to the scene.
	void add_crossroads();

	/// Adds sides to the scene.
	void add_sides();

	/// Changes text of the start_button.
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