#ifndef PROJDRILL_MACHINESHADOW_H
#define PROJDRILL_MACHINESHADOW_H
#include "QGraphicsItem"
#include "QColor"
#include"QGraphicsScene"
class MachineShadow : public QGraphicsRectItem {
public:
    MachineShadow(QPointF pos,int machine_id,QGraphicsScene *scene);
    void rotate();
	int machine_id;
	int rotate_count;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:

    QGraphicsScene *scene;
};
#endif//PROJDRILL_MACHINESHADOW_H
