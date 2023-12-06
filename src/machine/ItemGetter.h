#ifndef PROJDRILL_ITEMGETTER_H
#define PROJDRILL_ITEMGETTER_H
#include "QGraphicsItem"
#include "../item/ItemsBase.h"
#include <QGraphicsScene>
#include "QDebug"
class ItemGetter : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    ItemGetter(int posx, int posy,short towards, QGraphicsScene* scene) : QGraphicsRectItem(0, 0, 44, 44), towards(towards),scene(scene) {
        this->setZValue(3);//getter在sender上方
        this->setBrush(Qt::blue);
//        QGraphicsPixmapItem *item=new QGraphicsPixmapItem(QPixmap("./img/button/towards.png"));
//        item->setPos(posx,posy);
//        item->setTransformOriginPoint(22,22);
//        item->setRotation(90*towards);
//        item->setZValue(10);
//        scene->addItem(item);
		this->setOpacity(0.3);
        this->setPos(posx,posy);
        qDebug()<<"Getter_pos:"<<this->pos()<<"towards:"<<this->towards;
        scene->addItem(this);
        is_full=false;
    };
    int type() const override
	{
        return 23;
	}
    bool is_full;
	short towards;
public slots:
    void get_item(BasicItems* Item);
signals:
    void item_get(BasicItems* Item);
private:
    QGraphicsScene *scene;
};
#endif//PROJDRILL_ITEMGETTER_H
