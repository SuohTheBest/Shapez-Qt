#ifndef MACHINECONVEYOR_H
#define MACHINECONVEYOR_H
#define MAX_ITEM_HOLD 9
#define CONVEYOR_TIMER_MSEC 80

#include "MachineBase.h"
#include "QTimer"
#include "QQueue"

class MachineConveyor : public QObject, public MachineBase {
Q_OBJECT
public:
	MachineConveyor(QGraphicsScene *scene, QPointF &pos, short towards);

	static MachineBase *to_base(QGraphicsScene *scene, QPointF &pos, short towards);

	string detail_info() override;

	QTimer *timer;
public slots:

	void move_item();

	void add_item(BasicItems *new_item);

signals:

	void remove_item(BasicItems *remove_item);

private:
	QQueue<BasicItems *> items;
	static ::int8_t position_array[4][2];
	bool timer_running;
	short speed;
	ItemGetter *getter;
	ItemSender *sender;
};

#endif // MACHINECONVEYOR_H
