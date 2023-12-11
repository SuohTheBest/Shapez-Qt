#ifndef MACHINEDRILLER_H
#define MACHINEDRILLER_H
#define DRILLER_TIME 5000

#include "MachineBase.h"
#include "../map/MapBlockItem.h"

class MachineDriller : public QObject, public MachineBase {
Q_OBJECT
public:
	MachineDriller(QGraphicsScene *scene, QPointF &pos, short towards);

	static MachineBase *to_base(QGraphicsScene *scene, QPointF &pos, short towards);

	string detail_info() override;

	void pause()override;

	void restart()override;
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
