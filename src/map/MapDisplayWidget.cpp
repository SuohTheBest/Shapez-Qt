#include "MapDisplayWidget.h"
#include "MapCreator.h"
#include "QGraphicsItem"
#include "QGraphicsScene"
#include "QGraphicsSceneMouseEvent"

MapDisplayWidget::MapDisplayWidget(int layer, QWidget *parent) :
		layer(layer) {
	basic_info = new QLabel("details", this);
	basic_info->setFixedSize(200, 50);
	rotate_button = new RotateButton();
	QLabel *titleLabel = new QLabel("Debug");
	titleLabel->setFixedSize(200, 30);
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
	layout_main->addLayout(layout_tools);
	layout_tools->addWidget(construction_button);
	layout_tools->addWidget(rotate_button);
	layout_tools->addWidget(basic_info);
	layout_tools->addWidget(titleLabel);
	layout_tools->addWidget(debug_message);
	layout_main->setSpacing(15);
	setLayout(layout_main);
	connect(scene, &QGraphicsScene::selectionChanged, this, &MapDisplayWidget::handleSelectionChange);
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
				return;
			}
			scene->addItem(new_machine);
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
