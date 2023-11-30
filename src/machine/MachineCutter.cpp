#include "MachineCutter.h"
MachineCutter::MachineCutter(QGraphicsScene *scene,QPointF &pos): MachineBase(1,QPixmap(QString::fromStdString(img_path(1))),scene,pos)
{
    this->storage=new int[10];
}
MachineBase* MachineCutter::to_base(QGraphicsScene *scene,QPointF &pos) {
    return new MachineCutter(scene,pos);
}
