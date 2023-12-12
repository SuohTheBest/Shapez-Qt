#include "MachineCenter.h"

MachineCenter::MachineCenter(QGraphicsScene *scene, QPointF &pos, short towards, int gold, int level) :
		MachineBase(0, QPixmap(QString::fromStdString(img_path(0))), scene, pos, towards), gold(
		gold), level(level), is_task_chosen(false) {
	int size = level + 1;
	for (int i = 0; i < level + 1; ++i) {
		getter.push_back(new ItemGetter(pos.x() + 44 * i, pos.y() - 44, 2, scene, this));
	}
	for (int i = 0; i < level + 1; ++i) {
		getter.push_back(new ItemGetter(pos.x() + 44 * size, pos.y() + 44 * i, 3, scene, this));
	}
	for (int i = 0; i < level + 1; ++i) {
		getter.push_back(new ItemGetter(pos.x() + 44 * size - 44 * i - 44, pos.y() + 44 * size, 0, scene, this));
	}
	for (int i = 0; i < level + 1; ++i) {
		getter.push_back(new ItemGetter(pos.x() - 44, pos.y() + 44 * i, 1, scene, this));
	}
	for (int i = 0; i < getter.size(); ++i) {
		connect(getter[i], SIGNAL(item_get(BasicItems * )), this, SLOT(get_items(BasicItems * )));
	}
}

void MachineCenter::get_items(BasicItems *item) {
	gold += item->value;
	if (is_task_chosen && item->item_id == task.task_item_id) {
		task.task_item_remaining--;
		if (task.task_item_remaining == 0) {
			emit task_finished(task.task_id);
			is_task_chosen = false;
		}
	}
	delete item;
}

MachineBase *MachineCenter::to_base(QGraphicsScene *scene, QPointF &pos, short towards) {
	return new MachineCenter(scene, pos, towards);
}

string MachineCenter::detail_info() {
	return MachineBase::detail_info() + "\ngold:" + to_string(gold) + "\ntask_index:" + to_string(task.task_id) +
		   "\nremaining:" +
		   to_string(task.task_item_remaining);
}

void MachineCenter::set_task(int task_index) {
	switch (task_index) {
		case 1: {
			task = Task(task_index, 0, 20, 20);
			break;
		}
		case 2: {
			task = Task(task_index, 1, 10, 10);
			break;
		}
		case 3: {
			task = Task(task_index, 2, 30, 30);
			break;
		}
		default: {
			break;
		}
	}
	is_task_chosen = true;
}

void MachineCenter::set_task(int id, int a, int b, int c) {
	task = Task(id, a, b, c);
	is_task_chosen = true;
}
