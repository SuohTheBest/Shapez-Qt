#ifndef PROJDRILL_MACHINECUTTER_H
#define PROJDRILL_MACHINECUTTER_H

#include "MachineBase.h"

class MachineCutter : public QObject, public MachineBase {
Q_OBJECT
public:
	MachineCutter(QGraphicsScene *scene, QPointF &pos, short towards);

	static MachineBase *to_base(QGraphicsScene *scene, QPointF &pos, short towards);

	string detail_info()override;
public slots:

	void cut(BasicItems *item);

signals:

	void finish_cut_1(BasicItems *item1);

	void finish_cut_2(BasicItems *item2);

private:
	int speed;
	ItemGetter *getter;
	ItemSender *sender[2];
};

#endif//PROJDRILL_MACHINECUTTER_H
