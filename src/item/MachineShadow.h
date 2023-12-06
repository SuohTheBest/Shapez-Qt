#ifndef PROJDRILL_MACHINESHADOW_H
#define PROJDRILL_MACHINESHADOW_H

#include "QGraphicsItem"
#include "QColor"
#include"QGraphicsScene"

class MachineShadow {
public:
	//MachineShadow(QPointF pos, int machine_id, QGraphicsScene *scene);

	MachineShadow(QGraphicsScene *scene);

	void rotate();

	void setPos(QPointF pos);

	void setup(QPointF pos, int machine_id);

	void destory();

	int machine_id;
	int rotate_count;
	bool is_setup;
private:
	void _destory_real();

	QGraphicsRectItem *rect;
	QGraphicsPixmapItem *arrow;
	QGraphicsItemGroup *group;
	QGraphicsScene *scene;
};

#endif//PROJDRILL_MACHINESHADOW_H
