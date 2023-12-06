#include "MachineRubbishBin.h"

MachineRubbishBin::MachineRubbishBin(QGraphicsScene *scene, QPointF &pos, short towards) :
		MachineBase(2, QPixmap(QString::fromStdString(img_path(2))), scene, pos, towards) {
	for (int i = 0; i < 4; ++i) {
		getter[i]=new ItemGetter(pos.x()+44*position[i][0],pos.y()+44*position[i][1],(6+i)%4,scene);//2 3 0 1
		connect(getter[i], SIGNAL(item_get(BasicItems *)), this, SLOT(destory_item(BasicItems *)));
	}
}

MachineBase *MachineRubbishBin::to_base(QGraphicsScene *scene, QPointF &pos, short towards) {
	return new MachineRubbishBin(scene, pos, towards);
}

void MachineRubbishBin::destory_item(BasicItems* item) {
	delete item;
}
