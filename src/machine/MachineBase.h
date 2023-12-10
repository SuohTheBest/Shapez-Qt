#ifndef MACHINEBASE_H
#define MACHINEBASE_H

#include <tuple>
#include <string>
#include "../BaseDefinitions.h"
#include "QGraphicsScene"
#include "QGraphicsPixmapItem"
#include "../item/ItemsBase.h"
#include "ItemSender.h"
#include "ItemGetter.h"
#include "QDebug"

using namespace std;


class MachineBase : public QGraphicsPixmapItem {
public:
	int machine_id;
	const static int machine_size[TYPES_OF_MACHINES][2];
	const static string machine_info[TYPES_OF_MACHINES];

	static MachineBase *(*to_base[TYPES_OF_MACHINES])(QGraphicsScene *scene, QPointF &pos, short towards);

	MachineBase(int machine_id, const QPixmap &pixmap, QGraphicsScene *scene, QPointF &pos, short towards) :
			QGraphicsPixmapItem(pixmap, nullptr), machine_id(machine_id), towards(
			towards), scene(scene) {
		this->setTransformOriginPoint(22 * machine_size[machine_id][0], 22 * machine_size[machine_id][0]);
		this->setPos(pos);
		this->setFlag(this->ItemIsSelectable, true);
		this->setZValue(3);
		this->setRotation(90 * towards);
	};

	int size_x();

	int size_y();

	virtual string detail_info();

	virtual bool is_legal(BasicItems* item);

	string img_path();

	static string img_path(int item_type);

	int type() const override {
		return 21;
	}
	//void place(QGraphicsScene* scene,int rotate_count);// 0~3
protected:
	const static int position[4][2];
	short towards;
	QGraphicsScene *scene;
};

#endif//MACHINEBASE_H

