#ifndef PROJDRILL_MACHINERUBBISHBIN_H
#define PROJDRILL_MACHINERUBBISHBIN_H

#include "MachineBase.h"
/**
 * @brief 垃圾桶
 */
class MachineRubbishBin : public QObject, public MachineBase {
Q_OBJECT
public:
	MachineRubbishBin(QGraphicsScene *scene, QPointF &pos, short towards);

	static MachineBase *to_base(QGraphicsScene *scene, QPointF &pos, short towards);

	void set_disable()override;
public slots:

	void destory_item(BasicItems *item);

private:
	ItemGetter *getter[4];
};

#endif//PROJDRILL_MACHINERUBBISHBIN_H
