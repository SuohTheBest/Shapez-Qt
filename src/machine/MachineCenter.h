#ifndef PROJDRILL_MACHINECENTER_H
#define PROJDRILL_MACHINECENTER_H

#include "MachineBase.h"

class MachineCenter : public QObject, public MachineBase {
Q_OBJECT
public:
	MachineCenter(QGraphicsScene *scene, QPointF &pos, short towards);

	static MachineBase *to_base(QGraphicsScene *scene, QPointF &pos, short towards);

	string detail_info() override;

	int gold;
public slots:

	void get_items(BasicItems *item);

private:

	int level;
	vector<ItemGetter *> getter;
};

#endif//PROJDRILL_MACHINECENTER_H
