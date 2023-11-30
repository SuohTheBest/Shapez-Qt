#include "MachineCenter.h"
MachineCenter::MachineCenter(QGraphicsScene *scene,QPointF &pos): MachineBase(0,QPixmap(QString::fromStdString(img_path(0))),scene,pos)
{
    this->storage=new int[10];
}
MachineBase *MachineCenter::to_base(QGraphicsScene *scene,QPointF &pos) {
    return new MachineCenter(scene,pos);
}
