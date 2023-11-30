#ifndef MACHINEBASE_H
#define MACHINEBASE_H

#include <tuple>
#include <string>
#include "../BaseDefinitions.h"
#include "QGraphicsScene"
#include "QGraphicsPixmapItem"
#include "../item/ItemsBase.h"
#include "ItemSender.h"
#include "ItemGetter.h"
#include "QDebug"

using namespace std;

class MachineBase :public QGraphicsPixmapItem{
public:
    int machine_id;
    const static int machine_size[TYPES_OF_MACHINES][2];
    const static string machine_info[TYPES_OF_MACHINES];
    static MachineBase* (*to_base[TYPES_OF_MACHINES])(QGraphicsScene *scene);
    MachineBase(int machine_id, const QPixmap &pixmap,QGraphicsScene *scene):QGraphicsPixmapItem(pixmap,nullptr),machine_id(machine_id),scene(scene),towards(0){};
    int size_x();
    int size_y();
    string detail_info();
    string img_path();
    static string img_path(int type);
    //void place(QGraphicsScene* scene,int rotate_count);// 0~3
protected:
    short towards;
    QGraphicsScene *scene;
};
#endif//MACHINEBASE_H

