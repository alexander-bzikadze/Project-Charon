#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>

class Model_visualisation : public QWidget
{
public:
	Model_visualisation(QWidget *parent = 0);
	~Model_visualisation() = default;

	QGraphicsItem* add_line(QPointF const& p1, QPointF const& p2, qreal circle_size);
	QGraphicsItem* add_circle(qreal circe_size, QColor color = Qt::black);

	void fix_item(QGraphicsItem* item);
	void move_item(QGraphicsItem* item, QPointF const& new_point);
	void delete_item(QGraphicsItem* item);

private:
	QGraphicsScene mScene;
	QGraphicsView *mView;
};