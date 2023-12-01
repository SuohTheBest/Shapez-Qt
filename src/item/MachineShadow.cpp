#include "MachineShadow.h"
#include "../BaseDefinitions.h"
const int machine_size[TYPES_OF_MACHINES][2]={{4,4},{2,1},{1,1},{1,1},{1,1}};

MachineShadow::MachineShadow(QPointF pos, int machine_id, QGraphicsScene *scene)
    : QGraphicsRectItem(0, 0, 44*machine_size[machine_id][0], 44*machine_size[machine_id][1], nullptr),
      machine_id(machine_id),
      scene(scene) {
    this->rotate_count=0;
    this->setPos(pos);
    this->setTransformOriginPoint(this->boundingRect().topLeft());
    this->setBrush(QColor(255, 165, 0));
    this->setOpacity(0.7);
    this->setZValue(6);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene->addItem(this);
}

void MachineShadow::rotate() {
    this->setRotation(90);
    this->rotate_count++;
}
void MachineShadow::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (isSelected()) {

    }
    QGraphicsRectItem::mousePressEvent(event);
}
