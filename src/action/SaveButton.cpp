#include "SaveButton.h"
#include "iostream"
#include "src/machine/MachineConveyor.h"
#include "src/machine/MachineCenter.h"
#include <unistd.h>
#include <fstream>
#include "../action/choosetask.h"

using namespace std;

SaveButton::SaveButton(short (&map)[64][64], QList<MachineBase *> &machine_list, float *mul_1, float *mul_2, float *mul_3) :
		QPushButton(), machine_list(machine_list), map(map), mul_1(mul_1), mul_2(mul_2), mul_3(mul_3) {
	this->setToolTip("保存");
	this->setFixedSize(QSize(144, 144));
	this->setIcon(QIcon("./img/button/save.png"));
	this->setEnabled(true);
	connect(this, &SaveButton::clicked, this, &SaveButton::on_clicked);
	this->saveWidget = new SaveWidget();
	connect(saveWidget, SIGNAL(send_data(short)), this, SLOT(save(short)));
}

void SaveButton::on_clicked() {
	emit pause();
	saveWidget->show();
}

void SaveButton::save(short data_chosen) {
	if (access("./data/savedata", F_OK == -1)) {
		mkdir("./data/savedata");
	}
	string path = "./data/savedata/save0" + to_string(data_chosen);
	if (access(path.c_str(), F_OK == -1)) {
		mkdir(path.c_str());
	}
	QString file_name = QString::fromStdString(path + "/data.json");
	QFile save_file(file_name);
	if (!save_file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		qDebug() << "File open error";
		return;
	}
	QTextStream stream(&save_file);
	stream.setCodec("UTF-8");
	QJsonDocument doc;
	QJsonObject rootobj;
	int i = 0;
	int g_gold;
	rootobj.insert("mul_1",*mul_1);
	rootobj.insert("mul_2",*mul_2);
	rootobj.insert("mul_3",*mul_3);
	for (MachineBase *machine_item: machine_list) {
		QJsonObject obj;
		QJsonArray pos_array;
		obj.insert("machine_id", machine_item->machine_id);
		pos_array.append(machine_item->pos().x());
		pos_array.append(machine_item->pos().y());
		obj.insert("pos", pos_array);
		obj.insert("towards", machine_item->towards);
		if (machine_item->machine_id == 4) {
			QJsonArray item_array;
			MachineConveyor *conveyor = dynamic_cast<MachineConveyor *>(machine_item);
			obj.insert("turns", conveyor->turns);
			for (BasicItems *item: conveyor->items) {
				QJsonObject item_obj;
				QJsonArray item_pos_array;
				item_obj.insert("item_id", item->item_id);
				item_pos_array.append(item->pos().x());
				item_pos_array.append(item->pos().y());
				item_obj.insert("pos", item_pos_array);
				item_array.append(item_obj);
			}
			obj.insert("items", item_array);
		} else if (machine_item->machine_id == 0) {
			MachineCenter *center = dynamic_cast<MachineCenter *>(machine_item);
			obj.insert("gold", center->gold);
			g_gold = center->gold;
			obj.insert("is_task_chosen", center->is_task_chosen);
			QJsonObject task_obj;
			task_obj.insert("task_id", center->task.task_id);
			task_obj.insert("task_item_id", center->task.task_item_id);
			task_obj.insert("task_item_required", center->task.task_item_required);
			task_obj.insert("task_item_remaining", center->task.task_item_remaining);
			obj.insert("task", task_obj);
			QJsonArray task_arr;
			task_arr.append(ChooseTask::get_task(0));
			task_arr.append(ChooseTask::get_task(1));
			task_arr.append(ChooseTask::get_task(2));
			obj.insert("task_finished", task_arr);
		}
		rootobj.insert(QString::fromStdString("machine" + to_string(i++)), obj);
	}
	doc.setObject(rootobj);
	stream << doc.toJson();
	save_file.close();

	QFile g_save("./data/savedata/save00/save.json");
	if (!g_save.open(QFile::ReadOnly | QFile::Text)) {
		qDebug() << "Open error";
		return;
	}
	QTextStream g_stream(&g_save);
	g_stream.setCodec("UTF-8");
	QString g_str = g_stream.readAll();
	g_save.close();
	QJsonParseError jsonError;
	QJsonDocument g_doc = QJsonDocument::fromJson(g_str.toUtf8(), &jsonError);
	if (jsonError.error != QJsonParseError::NoError && !g_doc.isNull()) {
		qDebug() << "Json格式错误" << jsonError.error;
		return;
	}
	QJsonObject g_root_obj = g_doc.object();
	g_root_obj["gold"] = g_gold;
	g_doc.setObject(g_root_obj);
	if (!g_save.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Failed to open file";
		return;
	}
	g_save.write(g_doc.toJson());
	g_save.close();
	emit restart();
}
