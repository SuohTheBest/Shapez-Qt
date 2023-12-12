#ifndef PROJDRILL_MACHINECENTER_H
#define PROJDRILL_MACHINECENTER_H

#include "MachineBase.h"

struct Task {
	short task_id;
	short task_item_id;
	short task_item_required;
	short task_item_remaining;

	Task(int task_id,int task_item_id, int task_item_required, int task_item_remaining) :task_id(task_id),
			task_item_id(task_item_id), task_item_required(task_item_required), task_item_remaining(
			task_item_remaining) {};

	Task() :
			task_id(0),task_item_id(0), task_item_remaining(0), task_item_required(0) {};
};

class MachineCenter : public QObject, public MachineBase {
Q_OBJECT
public:
	MachineCenter(QGraphicsScene *scene, QPointF &pos, short towards, int gold = 0, int level = 1);

	static MachineBase *to_base(QGraphicsScene *scene, QPointF &pos, short towards);

	string detail_info() override;

	void set_task(int task_index);

	void set_task(int id,int a, int b, int c);

	int gold;
	int level;
	Task task;
	bool is_task_chosen;//TODO:data array
public slots:

	void get_items(BasicItems *item);

signals:

	void task_finished(int id);

private:

	vector<ItemGetter *> getter;
};

#endif//PROJDRILL_MACHINECENTER_H
