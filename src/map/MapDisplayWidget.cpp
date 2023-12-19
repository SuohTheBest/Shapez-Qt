#include "MapDisplayWidget.h"
#include "MapCreator.h"
#include "QGraphicsItem"
#include "QGraphicsScene"
#include "QGraphicsSceneMouseEvent"
#include "../action/choosetask.h"

MapDisplayWidget::MapDisplayWidget(QWidget *parent) {
	basic_info = new QLabel("details", this);
	basic_info->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	basic_info->setFixedHeight(75);
	rotate_button = new RotateButton();
	save_button = new SaveButton(map, machine_placed, &driller_speed_multiplier, &conveyer_speed_multiplier,
								 &cutter_speed_multiplier);
	connect(save_button, SIGNAL(pause()), this, SLOT(pause()));
	connect(save_button, SIGNAL(restart()), this, SLOT(restart()));
	QLabel *titleLabel = new QLabel("Debug");
	titleLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	titleLabel->setFixedHeight(30);
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setStyleSheet("color: green;");
	debug_message = new QTextEdit;
	debug_message->setPlainText("");
	debug_message->setReadOnly(true);
	scene = new QGraphicsScene();
	shadow = new MachineShadow(scene);
	view = new QGraphicsView(scene);
	rotate_button->set_shadow(shadow);
	scene->setBackgroundBrush(Qt::white);
	pause_button = new PauseButton();
	back_button = new BackToMenuButton();
	delete_button = new DeleteButton();
	memset(map_item_placed, -1, sizeof(map_item_placed));
	delete_machine = nullptr;
	read_global_levelup();
	for (int i = 0; i < 64; ++i) {
		for (int j = 0; j < 64; ++j) {
			QPixmap block;
			block.load(QString::fromStdString(pic_path(map[i][j])));
			MapBlockItem *blockItem = new MapBlockItem(block);
			scene->addItem(blockItem);
			blockItem->setPos(j * block.width(), i * block.height());
			blockItem->setFlag(blockItem->ItemIsSelectable, true);
			blockItem->set_type(map[i][j]);
			blockItem->setZValue(0);
		}
	}
	//设置layout
	view->setSceneRect(0, 0, 64 * 44, 64 * 44);
	construction_button = new ConstructionButton(scene);
	layout_main = new QHBoxLayout();
	layout_main->addWidget(view);
	basic_info->setAlignment(Qt::AlignCenter);
	basic_info->setStyleSheet("background-color: gray; border: 1px solid black; padding: 5px;");
	layout_tools = new QVBoxLayout();
	QGridLayout *gridlayout = new QGridLayout;
	layout_main->addLayout(layout_tools);
	gridlayout->addWidget(construction_button, 0, 0);
	gridlayout->addWidget(rotate_button, 0, 1);
	gridlayout->addWidget(save_button, 1, 1);
	gridlayout->addWidget(pause_button, 0, 2);
	gridlayout->addWidget(back_button, 1, 2);
	gridlayout->addWidget(delete_button, 1, 0);
	connect(back_button, SIGNAL(clicked()), this, SLOT(handle_back_button_clicked()));
	connect(pause_button, SIGNAL(clicked()), this, SLOT(handle_pause_button_clicked()));
	layout_tools->addLayout(gridlayout);
	layout_tools->addWidget(basic_info);
	layout_tools->addWidget(titleLabel);
	layout_tools->addWidget(debug_message);
	layout_tools->setMargin(25);
	layout_main->setSpacing(15);
	setLayout(layout_main);
	connect(scene, &QGraphicsScene::selectionChanged, this, &MapDisplayWidget::handleSelectionChange);
	QPointF center_pos(30 * 44, 30 * 44);
	center = new MachineCenter(scene, center_pos, 0, gold, center_size, gold_plus);
	machine_placed.append(center);
	construction_button->add_item_to_map(map_item_placed, center);
	connect(center, SIGNAL(task_finished(int)), this, SLOT(handle_task_finished(int)));
    play_music();
}

MapDisplayWidget::MapDisplayWidget(short save_chosen) {
	basic_info = new QLabel("details", this);
	basic_info->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	basic_info->setFixedHeight(75);
	rotate_button = new RotateButton();
	save_button = new SaveButton(map, machine_placed, &driller_speed_multiplier, &conveyer_speed_multiplier,
								 &cutter_speed_multiplier);
	connect(save_button, SIGNAL(pause()), this, SLOT(pause()));
	connect(save_button, SIGNAL(restart()), this, SLOT(restart()));
	QLabel *titleLabel = new QLabel("Debug");
	titleLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	titleLabel->setFixedHeight(30);
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setStyleSheet("color: green;");
	debug_message = new QTextEdit;
	debug_message->setPlainText("");
	debug_message->setReadOnly(true);
	scene = new QGraphicsScene();
	shadow = new MachineShadow(scene);
	view = new QGraphicsView(scene);
	rotate_button->set_shadow(shadow);
	scene->setBackgroundBrush(Qt::white);
	pause_button = new PauseButton();
	back_button = new BackToMenuButton();
	delete_button = new DeleteButton();
	delete_machine = nullptr;
	memset(map_item_placed, -1, sizeof(map_item_placed));

	string path = "./data/savedata/save0" + to_string(save_chosen);
	read_global_levelup();
	for (int i = 0; i < 64; ++i) {
		for (int j = 0; j < 64; ++j) {
			QPixmap block;
			block.load(QString::fromStdString(pic_path(map[i][j])));
			MapBlockItem *blockItem = new MapBlockItem(block);
			scene->addItem(blockItem);
			blockItem->setPos(j * block.width(), i * block.height());
			blockItem->setFlag(blockItem->ItemIsSelectable, true);
			blockItem->set_type(map[i][j]);
			blockItem->setZValue(0);
		}
	}
	view->setSceneRect(0, 0, 64 * 44, 64 * 44);
	construction_button = new ConstructionButton(scene);
	layout_main = new QHBoxLayout();
	layout_main->addWidget(view);
	basic_info->setAlignment(Qt::AlignCenter);
	basic_info->setStyleSheet("background-color: gray; border: 1px solid black; padding: 5px;");
	layout_tools = new QVBoxLayout();
	QGridLayout *gridlayout = new QGridLayout;
	layout_main->addLayout(layout_tools);
	gridlayout->addWidget(construction_button, 0, 0);
	gridlayout->addWidget(rotate_button, 0, 1);
	gridlayout->addWidget(save_button, 1, 1);
	gridlayout->addWidget(pause_button, 0, 2);
	gridlayout->addWidget(back_button, 1, 2);
	gridlayout->addWidget(delete_button, 1, 0);
	connect(back_button, SIGNAL(clicked()), this, SLOT(handle_back_button_clicked()));
	connect(pause_button, SIGNAL(clicked()), this, SLOT(handle_pause_button_clicked()));
	layout_tools->addLayout(gridlayout);
	layout_tools->addWidget(basic_info);
	layout_tools->addWidget(titleLabel);
	layout_tools->addWidget(debug_message);
	layout_tools->setMargin(25);
	layout_main->setSpacing(15);
	setLayout(layout_main);
	connect(scene, &QGraphicsScene::selectionChanged, this, &MapDisplayWidget::handleSelectionChange);
	//需要加载map_item_placed
	QFile data_file(QString::fromStdString(path + "/data.json"));
	if (!data_file.open(QFile::ReadOnly | QFile::Text)) {
		qDebug() << "Open error";
		return;
	}
	QTextStream stream(&data_file);
	stream.setCodec("UTF-8");
	QString str = stream.readAll();
	data_file.close();
	QJsonParseError jsonError;
	QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
	if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
		qDebug() << "Json格式错误" << jsonError.error;
		return;
	}
	QJsonObject root_obj = doc.object();
	int i = 0;
	driller_speed_multiplier = root_obj.value("mul_1").toDouble();
	conveyer_speed_multiplier = root_obj.value("mul_2").toDouble();
	cutter_speed_multiplier = root_obj.value("mul_3").toDouble();
	for (;; i++) {
		QJsonValue machine_val = root_obj.value(QString::fromStdString("machine" + to_string(i)));
		if (machine_val.isNull() || machine_val.type() != QJsonValue::Object)break;
		QJsonObject machine_obj = machine_val.toObject();
		QPointF machine_pos = QPointF(machine_obj.value("pos").toArray().at(0).toInt(),
									  machine_obj.value("pos").toArray().at(1).toInt());
		int machine_id = machine_obj.value("machine_id").toInt();
		if (machine_id == 0) {
			MachineCenter *_center = new MachineCenter(scene, machine_pos, 0, gold, center_size, gold_plus);
			this->center = _center;
			machine_placed.append(center);
			construction_button->add_item_to_map(map_item_placed, center);
			center->is_task_chosen = machine_obj.value("is_task_chosen").toBool();
			QJsonObject taskobj = machine_obj.value("task").toObject();
			center->task = Task(taskobj.value("task_id").toInt(), taskobj.value("task_item_id").toInt(),
								taskobj.value("task_item_required").toInt(),
								taskobj.value("task_item_remaining").toInt());
			QJsonArray taskarr = machine_obj.value("task_finished").toArray();
			for (int j = 0; j < 3; ++j) {
				ChooseTask::is_finished[j] = taskarr[j].toBool();
			}
			continue;
		}
		MachineBase *new_machine =
				MachineBase::to_base[machine_id](scene, machine_pos,
												 machine_obj.value("towards").toInt());
		if (construction_button->is_overlap(map_item_placed, new_machine)) {
			delete new_machine;
			continue;
		}
		machine_placed.append(new_machine);
		construction_button->add_item_to_map(map_item_placed, new_machine);
		if (new_machine->machine_id == 4) {
			MachineConveyor *conveyor = dynamic_cast<MachineConveyor *>(new_machine);
			conveyor->set_multiplier(&conveyer_speed_multiplier);
			conveyor->rotate(machine_obj.value("turns").toInt());
			QJsonArray items = machine_obj.value("items").toArray();
			for (auto item: items) {
				QJsonObject item_obj = item.toObject();
				QPointF item_pos = QPointF(item_obj.value("pos").toArray().at(0).toInt(),
										   item_obj.value("pos").toArray().at(1).toInt());
				BasicItems *new_item = new BasicItems(item_obj.value("item_id").toInt(), scene);
				new_item->setPos(item_pos);
				conveyor->items.append(new_item);
			}
		} else if (new_machine->machine_id == 1) {
			MachineCutter *cutter = dynamic_cast<MachineCutter *>(new_machine);
			cutter->set_multiplier(&cutter_speed_multiplier);
		} else if (new_machine->machine_id == 3) {
			MachineDriller *driller = dynamic_cast<MachineDriller *>(new_machine);
			driller->set_multiplier(&driller_speed_multiplier);
		}
		new_machine->pause();
	}
	connect(center, SIGNAL(task_finished(int)), this, SLOT(handle_task_finished(int)));
    play_music();
	restart();
}

void MapDisplayWidget::handleSelectionChange() {
	QList<QGraphicsItem *> selectedItems = scene->selectedItems();
	if (selectedItems.size() > 1) {
		for (int i = 1; i < selectedItems.size(); ++i) {
			selectedItems[i]->setSelected(false);
		}
	}
	if (selectedItems.size() == 0)return;
	QGraphicsItem *item = selectedItems[0];
	QPointF pos = item->pos();
	if (item->zValue() == 0)//地图上的物品
	{
		if (construction_button->machine_id == -1)//地图格且没有放置物品
		{
			MapBlockItem *map_block = dynamic_cast<MapBlockItem *>(item);
			if (map_block) {
				rotate_button->set_disable();
				basic_info->setText(QString::fromStdString(map_block->detail_info()));
				return;
			}
		} else if (!shadow->is_setup) { //准备放置物品
			rotate_button->set_enable(pos, construction_button->machine_id);
		} else if (shadow->machine_id == construction_button->machine_id) { //移动阴影
			shadow->setPos(pos);
		} else { //machine_id不符，玩家改变了选择
			rotate_button->set_disable();
		}
	} else if (item->zValue() == 6) { //点击阴影
		if (shadow->machine_id == construction_button->machine_id) { //放置机器
			MachineBase *new_machine =
					MachineBase::to_base[construction_button->machine_id](scene, pos, shadow->rotate_count % 4);
			if (construction_button->is_overlap(map_item_placed, new_machine)) {
				construction_button->machine_id = -1;
				delete new_machine;
				rotate_button->set_disable();
				return;
			}
			if (new_machine->machine_id == 4) {
				MachineConveyor *conveyor = dynamic_cast<MachineConveyor *>(new_machine);
				conveyor->set_multiplier(&conveyer_speed_multiplier);
			} else if (new_machine->machine_id == 1) {
				MachineCutter *cutter = dynamic_cast<MachineCutter *>(new_machine);
				cutter->set_multiplier(&cutter_speed_multiplier);
			} else if (new_machine->machine_id == 3) {
				MachineDriller *driller = dynamic_cast<MachineDriller *>(new_machine);
				driller->set_multiplier(&driller_speed_multiplier);
			}
			machine_placed.append(new_machine);
			construction_button->add_item_to_map(map_item_placed, new_machine);
			construction_button->machine_id = -1;
			rotate_button->set_disable();
		} else { //玩家改变了选择
			rotate_button->set_disable();
		}
	} else { //机器
		if (shadow->is_setup) {
			rotate_button->set_disable();
		}
		construction_button->machine_id = -1;
		MachineBase *machine = dynamic_cast<MachineBase *>(item);
		if (delete_button->isChecked() && machine->machine_id != 0) {
			if (delete_machine != nullptr)delete delete_machine;
			machine->setSelected(false);
			scene->removeItem(machine);
			machine_placed.removeOne(machine);
			construction_button->remove_item_from_map(map_item_placed, machine);
			delete_machine = machine;
			machine->set_disable();
			delete_button->setChecked(false);
			return;
		}
		debug_message->setText(QString::fromStdString(machine->detail_info()));
		if (machine->machine_id == 4) {
			rotate_button->set_conveyor(dynamic_cast<MachineConveyor *>(item));
		} else if (machine->machine_id == 0 && !center->is_task_chosen)//选中了center
		{
			rotate_button->set_disable();
			emit choose_task();
		} else {
			rotate_button->set_disable();
		}
	}
}

void MapDisplayWidget::pause() {
	for (MachineBase *machine: machine_placed) {
		machine->pause();
	}
	if (!pause_button->is_pause)pause_button->switch_state();
}

void MapDisplayWidget::restart() {
	for (MachineBase *machine: machine_placed) {
		machine->restart();
	}
	if (pause_button->is_pause)pause_button->switch_state();
}

void MapDisplayWidget::handle_pause_button_clicked() {
	if (!pause_button->is_pause) {
		pause();
	} else {
		restart();
	}
}

void MapDisplayWidget::handle_back_button_clicked() {
	pause();
    player->stop();
	emit back_to_menu();
}

void MapDisplayWidget::set_task(int n) {
	center->set_task(n);
}

void MapDisplayWidget::handle_task_finished(int n) {
	LevelUp *levelup = new LevelUp("局部强化", "强化开采器的速率\n(将开采器的速度\n提升为1.5倍)",
								   "强化传送带的速率\n(将传送带的速度\n提升为1.25倍)",
								   "强化切割机的速率\n(将切割机的速度\n提升为1.5倍)");
	connect(levelup, SIGNAL(send_levelup(int)), this, SLOT(level_up(int)));
	levelup->show();
	emit task_finished(n);
}

void MapDisplayWidget::level_up(int n) {
	switch (n) {
		case 1: {
			driller_speed_multiplier *= 1.5f;
			break;
		}
		case 2: {
			conveyer_speed_multiplier *= 1.25f;
			break;
		}
		case 3: {
			cutter_speed_multiplier *= 1.5f;
			break;
		}
		default: {
			break;
		}
	}
}

void MapDisplayWidget::read_global_levelup() {
	QString map_path("./data/savedata/save00/map.txt");
	QFile map_save(map_path);
	QString path("./data/savedata/save00/save.json");
	QFile save(path);
	if (!save.open(QFile::ReadOnly | QFile::Text) || !map_save.open(QFile::ReadOnly | QFile::Text)) {
		qDebug() << "Open error";
		return;
	}
	map_save.close();
	ifstream map_in(map_path.toStdString());
	memset(map, 0, sizeof(map));
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			int temp;
			map_in >> temp;
			map[i][j] = temp;
		}
	}
	map_in.close();
	QTextStream stream(&save);
	stream.setCodec("UTF-8");
	QString str = stream.readAll();
	save.close();
	QJsonParseError jsonError;
	QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
	if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
		qDebug() << "Json格式错误" << jsonError.error;
		return;
	}
	QJsonObject root_obj = doc.object();
	center_size = root_obj.value("center_size").toInt();
	gold_plus = root_obj.value("gold_plus").toInt();
	gold = root_obj.value("gold").toInt();
}

void MapDisplayWidget::play_music() {
    player = new QMediaPlayer;
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile("./img/Fading_into_the_Dream_Audio Denoise.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);
    player->play();

}
