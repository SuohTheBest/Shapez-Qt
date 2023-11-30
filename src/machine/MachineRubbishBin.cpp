#include "MachineRubbishBin.h"
MachineRubbishBin::MachineRubbishBin(QGraphicsScene *scene): MachineBase(2,QPixmap(QString::fromStdString(img_path(2))),scene)
{

}
MachineBase* MachineRubbishBin::to_base(QGraphicsScene *scene) {
    return new MachineRubbishBin(scene);
}
