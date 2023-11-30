#include "MachineDriller.h"
MachineDriller::MachineDriller(QGraphicsScene *scene): MachineBase(3,QPixmap(QString::fromStdString(img_path(3))),scene)
{

}
MachineBase* MachineDriller::to_base(QGraphicsScene *scene) {
    return new MachineDriller(scene);
}
