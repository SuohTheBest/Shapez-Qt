#include "MachineCenter.h"
MachineCenter::MachineCenter(QGraphicsScene *scene): MachineBase(0,QPixmap(QString::fromStdString(img_path(0))),scene)
{
    this->storage=new int[10];
}
MachineBase *MachineCenter::to_base(QGraphicsScene *scene) {
    return new MachineCenter(scene);
}
