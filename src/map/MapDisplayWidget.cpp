#include "MapDisplayWidget.h"
#include "MapCreator.h"
#include "QGraphicsItem"
#include "QGraphicsScene"
#include "QGraphicsSceneMouseEvent"

MapDisplayWidget::MapDisplayWidget(int layer, QWidget *parent) :
		layer(layer) {
	basic_info = new QLabel("details", this);
	basic_info->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	basic_info->setFixedHeight(75);
	rotate_button = new RotateButton();
	save_button = new SaveButton(map, machine_placed);
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
	back_button=new BackToMenuButton();

	memset(map_item_placed, -1, sizeof(map_item_placed));
	if (access(map_path(layer).c_str(), F_OK) == -1) {
		MapCreator *map = new MapCreator(layer);
		map->createMap();
	}

	ifstream map_in(map_path(layer));
	memset(map, 0, sizeof(map));
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			int temp;
			map_in >> temp;
			map[i][j] = temp;
		}
	}
	map_in.close();

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
	gridlayout->addWidget(back_button,1,2);
	connect(back_button, SIGNAL(clicked()),this, SLOT(handle_back_button_clicked()));
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
	center = dynamic_cast<MachineCenter *>(MachineBase::to_base[0](scene, center_pos, 0));
	machine_placed.append(center);
}

MapDisplayWidget::MapDisplayWidget(short save_chosen) :
		layer(0) {
	basic_info = new QLabel("details", this);
	basic_info->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	basic_info->setFixedHeight(75);
	rotate_button = new RotateButton();
	save_button = new SaveButton(map, machine_placed);
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
	back_button=new BackToMenuButton();
	memset(map_item_placed, -1, sizeof(map_item_placed));

	string path = "./data/savedata/save0" + to_string(save_chosen);
	ifstream map_in(path + "/map.txt");
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			int temp;
			map_in >> temp;
			map[i][j] = temp;
		}
	}
	map_in.close();
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
	gridlayout->addWidget(back_button,1,2);
	connect(back_button, SIGNAL(clicked()),this, SLOT(handle_back_button_clicked()));
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
	for (;; i++) {
		QJsonValue machine_val = root_obj.value(QString::fromStdString("machine" + to_string(i)));
		if (machine_val.isNull() || machine_val.type() != QJsonValue::Object)break;
		QJsonObject machine_obj = machine_val.toObject();
		QPointF machine_pos = QPointF(machine_obj.value("pos").toArray().at(0).toInt(),
									  machine_obj.value("pos").toArray().at(1).toInt());
		MachineBase *new_machine =
				MachineBase::to_base[machine_obj.value("machine_id").toInt()](scene, machine_pos,
																			  machine_obj.value("towards").toInt());
		machine_placed.append(new_machine);
		construction_button->add_item_to_map(map_item_placed, new_machine);
		if (new_machine->machine_id == 0) {
			MachineCenter *center = dynamic_cast<MachineCenter *>(new_machine);
			center->gold = machine_obj.value("gold").toInt();
			this->center = center;
		} else if (new_machine->machine_id == 4) {
			MachineConveyor *conveyor = dynamic_cast<MachineConveyor *>(new_machine);
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
		}
		new_machine->pause();
	}
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
		debug_message->setText(QString::fromStdString(machine->detail_info()));
		if (machine->machine_id == 4) {
			rotate_button->set_conveyor(dynamic_cast<MachineConveyor *>(item));
		} else {
			rotate_button->set_disable();
		}
	}
}

void MapDisplayWidget::pause() {
	for (MachineBase *machine: machine_placed) {
		machine->pause();
	}
	pause_button->switch_state();
}

void MapDisplayWidget::restart() {
	for (MachineBase *machine: machine_placed) {
		machine->restart();
	}
	pause_button->switch_state();
}

void MapDisplayWidget::handle_pause_button_clicked() {
	if (!pause_button->is_pause) {
		pause();
	} else {
		restart();
	}
}

void MapDisplayWidget::handle_back_button_clicked() {
	emit back_to_menu();
}
