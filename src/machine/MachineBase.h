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

/**
 * @brief 机器基类
 * @author SuohTheBest
 * @attention 添加新的机器时需要实现to_base函数，并添加到to_base数组中
 */
class MachineBase : public QGraphicsPixmapItem {
public:
	int machine_id;
	const static int machine_size[TYPES_OF_MACHINES][2];
	const static string machine_info[TYPES_OF_MACHINES];

	static MachineBase *(*to_base[TYPES_OF_MACHINES])(QGraphicsScene *scene, QPointF &pos, short towards);

	MachineBase(int machine_id, const QPixmap &pixmap, QGraphicsScene *scene, QPointF &pos, short towards) :
			QGraphicsPixmapItem(pixmap, nullptr), machine_id(machine_id), towards(
			towards), scene(scene) {
		if (machine_size[machine_id][0] == machine_size[machine_id][1])
			this->setTransformOriginPoint(22 * machine_size[machine_id][0], 22 * machine_size[machine_id][0]);
		else this->setTransformOriginPoint(22, 22);
		this->setPos(pos);
		this->setFlag(this->ItemIsSelectable, true);
		this->setZValue(3);
		this->setRotation(90 * towards);
		scene->addItem(this);
	};

	virtual int size_x();

	virtual int size_y();

	virtual string detail_info();

	virtual bool is_legal(BasicItems *item);

	virtual void pause();

	virtual void restart();

	virtual void set_disable();

	static string img_path(int item_type);

	int type() const override {
		return 21;
	}

	short towards;
protected:
	const static int position[4][2];
	QGraphicsScene *scene;
};

#endif//MACHINEBASE_H

