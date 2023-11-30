#ifndef MAPBLOCKITEM_H
#define MAPBLOCKITEM_H
#include "QGraphicsItem"
#include "MapCreator.h"
#include "string"
using namespace std;
class MapBlockItem:public QGraphicsPixmapItem{
public:
    using QGraphicsPixmapItem::QGraphicsPixmapItem;
    // 默认为0
    void set_type(int type);
    string detail_info();
    int type=0;

private:
    static string info[TYPE_OF_BLOCKS];
};

#endif // MAPBLOCKITEM_H
