#ifndef MACHINEDRILLER_H
#define MACHINEDRILLER_H

#include "MachineBase.h"
#include "../map/MapBlockItem.h"

class MachineDriller : public QObject, public MachineBase {
Q_OBJECT
public:
	MachineDriller(QGraphicsScene *scene, QPointF &pos, short towards);

	static MachineBase *to_base(QGraphicsScene *scene, QPointF &pos, short towards);

	void set_multiplier(float* multiply);

	string detail_info() override;

	void pause()override;

	void restart()override;

	void set_disable()override;

	float* multiplier;
public slots:

	void drill();

signals:

	void item_drilled(BasicItems *Item);

private:
	short item_id;
	ItemSender *sender;
	QTimer *timer;
};

#endif// MACHINEDRILLER_H
