#include "MachineShadow.h"
#include "math.h"
#include "../BaseDefinitions.h"

const int machine_size[TYPES_OF_MACHINES][2] = {{2, 2},
												{2, 1},
												{1, 1},
												{1, 1},
												{1, 1},
												{4, 1},
												{3, 1}};

MachineShadow::MachineShadow(QGraphicsScene *scene) :
		rect(nullptr), arrow(nullptr), group(nullptr), scene(scene) {
	is_setup = false;
}

void MachineShadow::setup(QPointF pos, int machine_id) {
	this->_destory_real();
	this->machine_id = machine_id;
	int size_x = machine_size[machine_id][0];
	int size_y = machine_size[machine_id][1];
	rect = new QGraphicsRectItem(0, 0, 44 * size_x, 44 * size_y, nullptr);
	this->rotate_count = 0;
	rect->setBrush(QColor(255, 165, 0));
	rect->setOpacity(0.2);
	QPixmap pixmap("./img/button/towards.png");
	arrow = new QGraphicsPixmapItem(pixmap);
	arrow->setPos(22 * size_x - 11, 22 * size_y - 18);
	group = new QGraphicsItemGroup();
	group->addToGroup(rect);
	group->addToGroup(arrow);
	group->setPos(pos);
	group->setFlag(QGraphicsItem::ItemIsSelectable);
	group->setZValue(6);
	if (size_x == size_y)group->setTransformOriginPoint(22 * size_x, 22 * size_x);
	else group->setTransformOriginPoint(22, 22);
	scene->addItem(group);
	is_setup = true;
}

void MachineShadow::rotate() {
	group->setRotation(90 + group->rotation());
	this->rotate_count++;
}

void MachineShadow::destory() {
	group->setPos(64 * 44 + 100, 64 * 44 + 100);
	is_setup = false;
}

void MachineShadow::_destory_real() {
	if (group) {
		scene->removeItem(group);
		delete group;
	}
}

void MachineShadow::setPos(QPointF pos) {
	group->setPos(pos);
}
