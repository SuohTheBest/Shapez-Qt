#include "MachineCenter.h"

MachineCenter::MachineCenter(QGraphicsScene *scene, QPointF &pos, short towards, int gold, int level, int gold_plus) :
		MachineBase(0, QPixmap(QString::fromStdString(img_path(0))).scaled(44*level,44*level), scene, pos, towards), gold(
		gold), level(level), gold_plus(gold_plus) {
	for (int i = 0; i < level ; ++i) {
		getter.push_back(new ItemGetter(pos.x() + 44 * i, pos.y() - 44, 2, scene, this));
	}
	for (int i = 0; i < level ; ++i) {
		getter.push_back(new ItemGetter(pos.x() + 44 * level, pos.y() + 44 * i, 3, scene, this));
	}
	for (int i = 0; i < level ; ++i) {
		getter.push_back(new ItemGetter(pos.x() + 44 * level - 44 * i - 44, pos.y() + 44 * level, 0, scene, this));
	}
	for (int i = 0; i < level ; ++i) {
		getter.push_back(new ItemGetter(pos.x() - 44, pos.y() + 44 * i, 1, scene, this));
	}
	for (int i = 0; i < getter.size(); ++i) {
		connect(getter[i], SIGNAL(item_get(BasicItems * )), this, SLOT(get_items(BasicItems * )));
	}
	is_task_chosen = false;
	this->setTransformOriginPoint(22 * machine_size[machine_id][0], 22 * machine_size[machine_id][0]);
	this->setFlag(this->ItemIsSelectable, true);
	this->setZValue(3);
	this->setRotation(90 * towards);
	scene->addItem(this);
	this->setPos(pos);
}

void MachineCenter::get_items(BasicItems *item) {
	gold += item->value + gold_plus;
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
	return MachineBase::detail_info() +"\nlevel:"+ to_string(level)+ "\ngold:" + to_string(gold) + "\ntask_index:" + to_string(task.task_id) +
		   "\nremaining:" +to_string(task.task_item_remaining)+"\ngold_plus:"+ to_string(gold_plus);
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

int MachineCenter::size_x() {
	return level;
}

int MachineCenter::size_y() {
	return level;
}

