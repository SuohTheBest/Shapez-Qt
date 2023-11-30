#ifndef ITEMSBASE_H
#define ITEMSBASE_H
#include "QGraphicsItem"
#include "QPixmap"
#include "QString"
#include "string"
using namespace std;
class BasicItems:public QGraphicsPixmapItem
{
public:
    BasicItems(int item_id):QGraphicsPixmapItem(QPixmap(QString::fromStdString("./img/machine/"+to_string(item_id)+".png")),nullptr),item_id(item_id),pixels_moved(0){};
    short item_id;
    short pixels_moved;
};

#endif
