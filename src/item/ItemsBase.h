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
    BasicItems(int item_id):QGraphicsPixmapItem(QPixmap(QString::fromStdString("./img/item/"+to_string(item_id)+".png")),nullptr),item_id(item_id),pixels_moved(0){
        this->setZValue(5);
    };
    short item_id;
    short pixels_moved;
};

#endif