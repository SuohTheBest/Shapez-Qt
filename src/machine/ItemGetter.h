#ifndef PROJDRILL_ITEMGETTER_H
#define PROJDRILL_ITEMGETTER_H
#include "QGraphicsItem"
#include "../item/ItemsBase.h"
#include <QGraphicsScene>
#include "QDebug"
class ItemGetter : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    ItemGetter(int posx, int posy, QGraphicsScene* scene) : QGraphicsRectItem(0, 0, 44, 44), scene(scene) {
        this->setZValue(3);//getter在sender上方
        this->setBrush(Qt::blue);
        this->setOpacity(0.3);
        this->setPos(posx,posy);
        qDebug()<<"Getter_pos:"<<this->pos();
        scene->addItem(this);
        is_full=false;
    };
    bool is_full;
public slots:
    void get_item(BasicItems* Item);
signals:
    void item_get(BasicItems* Item);
private:
    QGraphicsScene *scene;
};
#endif//PROJDRILL_ITEMGETTER_H
