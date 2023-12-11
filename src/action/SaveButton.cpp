#include "SaveButton.h"
#include "iostream"
#include "src/machine/MachineConveyor.h"
#include "src/machine/MachineCenter.h"
#include <unistd.h>
#include <fstream>

using namespace std;

SaveButton::SaveButton(short (&map)[64][64],QList<MachineBase *> &machine_list) :
		QPushButton(), machine_list(machine_list),map(map) {
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
	string path="./data/savedata/save0"+ to_string(data_chosen);
	if (access(path.c_str(), F_OK == -1)) {
		mkdir(path.c_str());
	}

	ofstream map_out(path+"/map.txt", ios::out);
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			map_out << map[i][j] << " ";
		}
		map_out << endl;
	}
	map_out.close();

	QString file_name=QString::fromStdString(path+"/data.json");
	QFile save_file(file_name);
	if (!save_file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		qDebug() << "File open error";
		return;
	}
	QTextStream stream(&save_file);
	stream.setCodec("UTF-8");
	QJsonDocument doc;
	QJsonObject rootobj;
	int i=0;

	for (MachineBase * machine_item:machine_list) {
		QJsonObject obj;
		QJsonArray pos_array;
		obj.insert("machine_id",machine_item->machine_id);
		pos_array.append(machine_item->pos().x());
		pos_array.append(machine_item->pos().y());
		obj.insert("pos",pos_array);
		obj.insert("towards",machine_item->towards);
		if(machine_item->machine_id==4)
		{
			QJsonArray item_array;
			MachineConveyor* conveyor=dynamic_cast<MachineConveyor*>(machine_item);
			for(BasicItems* item:conveyor->items)
			{
				QJsonObject item_obj;
				QJsonArray item_pos_array;
				item_obj.insert("item_id",item->item_id);
				item_pos_array.append(item->pos().x());
				item_pos_array.append(item->pos().y());
				item_obj.insert("pos",item_pos_array);
				item_array.append(item_obj);
			}
			obj.insert("items",item_array);
		} else if(machine_item->machine_id==0)
		{
			MachineCenter* center=dynamic_cast<MachineCenter*>(machine_item);
			obj.insert("gold",center->gold);
		}
		rootobj.insert(QString::fromStdString("machine"+ to_string(i++)),obj);
	}
	doc.setObject(rootobj);
	stream<<doc.toJson();
	save_file.close();
	emit restart();
}