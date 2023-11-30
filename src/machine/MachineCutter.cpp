#include "MachineCutter.h"
MachineCutter::MachineCutter(QGraphicsScene *scene): MachineBase(1,QPixmap(QString::fromStdString(img_path(1))),scene)
{
    this->storage=new int[10];
}
MachineBase* MachineCutter::to_base(QGraphicsScene *scene) {
    return new MachineCutter(scene);
}
