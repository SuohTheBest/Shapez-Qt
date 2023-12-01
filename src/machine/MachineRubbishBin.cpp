#include "MachineRubbishBin.h"

MachineRubbishBin::MachineRubbishBin(QGraphicsScene *scene, QPointF &pos,short towards) :
		MachineBase(2, QPixmap(QString::fromStdString(img_path(2))), scene, pos,towards) {

}

MachineBase *MachineRubbishBin::to_base(QGraphicsScene *scene, QPointF &pos,short towards) {
	return new MachineRubbishBin(scene, pos,towards);
}
