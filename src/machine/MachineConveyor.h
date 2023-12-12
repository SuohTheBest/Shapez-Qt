#ifndef MACHINECONVEYOR_H
#define MACHINECONVEYOR_H
#define MAX_ITEM_HOLD 7

#include "MachineBase.h"
#include "QTimer"
#include "QQueue"

class MachineConveyor : public QObject, public MachineBase {
Q_OBJECT
public:
	MachineConveyor(QGraphicsScene *scene, QPointF &pos, short towards);

	static MachineBase *to_base(QGraphicsScene *scene, QPointF &pos, short towards);

	void set_multiplier(float *multiply);

	string detail_info() override;

	bool is_legal(BasicItems *item) override;

	void pause() override;

	void restart() override;

	void rotate();

	void rotate(int turns);

	QTimer *timer;
	QQueue<BasicItems *> items;
	short turns;
	float *multiplier;
public slots:

	void move_item();

	void add_item(BasicItems *new_item);

signals:

	void remove_item(BasicItems *remove_item);

private:
	bool timer_running;
	short speed;

	ItemGetter *getter;
	ItemSender *sender;

	QPointF end_pos();

	QPointF mid_pos(BasicItems *item);

	int distance(QPointF curr, QPointF prev);

	bool is_distance_enough(QPointF curr, QPointF prev);
};

#endif // MACHINECONVEYOR_H
