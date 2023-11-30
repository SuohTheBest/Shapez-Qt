#include "MachineRubbishBin.h"
MachineRubbishBin::MachineRubbishBin(QGraphicsScene *scene,QPointF &pos): MachineBase(2,QPixmap(QString::fromStdString(img_path(2))),scene,pos)
{

}
MachineBase* MachineRubbishBin::to_base(QGraphicsScene *scene,QPointF &pos) {
    return new MachineRubbishBin(scene,pos);
}
