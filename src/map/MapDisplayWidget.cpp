#include "MapDisplayWidget.h"
#include "MapCreator.h"
#include "QGraphicsItem"
#include "QGraphicsScene"
#include "QGraphicsSceneMouseEvent"

MapDisplayWidget::MapDisplayWidget(int layer, QWidget *parent) : layer(layer)
{
    basic_info = new QLabel("details", this);
    basic_info->setFixedSize(200,50);
    QLabel *titleLabel = new QLabel("Debug");
    titleLabel->setFixedSize(200,30);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: green;");

    debug_message = new QTextEdit;
    debug_message->setPlainText("");
    debug_message->setReadOnly(true);
    scene = new QGraphicsScene();

    view = new QGraphicsView(scene);
    scene->setBackgroundBrush(Qt::white);
    memset(map_item_placed,-1,sizeof(map_item_placed));
    if (access(map_path(layer).c_str(), F_OK) == -1) {
        MapCreator *map = new MapCreator(layer);
        map->createMap();
    }

    ifstream map_in(map_path(layer));
    int map[64][64];
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
            MapBlockItem *blockItem= new MapBlockItem(block);
            scene->addItem(blockItem);
            blockItem->setPos(j * block.width(), i * block.height());
            blockItem->setFlag(blockItem->ItemIsSelectable, true);
            blockItem->set_type(map[i][j]);
            blockItem->setZValue(0);
        }
    }

    //设置layout
    view->resize(64 * 44, 64 * 44);
    construction_button = new ConstructionButton(scene);
    layout_main = new QHBoxLayout();
    layout_main->addWidget(view);
    basic_info->setAlignment(Qt::AlignCenter);
    basic_info->setStyleSheet("background-color: gray; border: 1px solid black; padding: 5px;");
    layout_tools = new QVBoxLayout();
    layout_main->addLayout(layout_tools);
    layout_tools->addWidget(construction_button);
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
    QGraphicsItem *item = selectedItems[0];
    QPointF pos=item->pos();

    if(construction_button->machine_id!=-1)
    {
        MachineBase* new_machine=MachineBase::to_base[construction_button->machine_id](scene,pos);
        //不合法的操作
        if(item->zValue()>0||construction_button->is_overlap(map_item_placed,new_machine))
        {
            construction_button->machine_id=-1;
            delete new_machine;
            return;
        }
        scene->addItem(new_machine);
        machine_placed.append(new_machine);
        construction_button->add_item_to_map(map_item_placed,new_machine);
        construction_button->machine_id=-1;
    }
    else {
        MapBlockItem *map_block = qgraphicsitem_cast<MapBlockItem *>(item);
        if (map_block) {
            basic_info->setText(QString::fromStdString(map_block->detail_info()));
            return;
        }
        MachineBase *machine_item = qgraphicsitem_cast<MachineBase *>(item);
        if (machine_item) {
            basic_info->setText(QString::fromStdString(machine_item->detail_info()));
            return;
        }
    }
}


void MapDisplayWidget::keyPressEvent(QKeyEvent *event) {
    //TODO
}

void MapDisplayWidget::mousePressEvent(QMouseEvent *event) {
    //TODO
}
