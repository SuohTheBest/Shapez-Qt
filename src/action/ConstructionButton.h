#ifndef CONSTRUCTIONBUTTON_H
#define CONSTRUCTIONBUTTON_H

#include"../machine/MachineBase.h"
#include"string"
#include"QToolButton"
#include"QMenu"
#include"QAction"
#include"QSignalMapper"
#include"QGraphicsScene"

using namespace std;
/**
 * @brief 负责建造的按钮，也负责检测是否重叠，重叠时将无法放置物体
 */
class ConstructionButton : public QToolButton {
Q_OBJECT
public:
	ConstructionButton(QGraphicsScene *scene, QWidget *parent = nullptr);

	int machine_id;

	bool is_overlap(QList<MachineBase *> &data, MachineBase *new_item);

	bool is_overlap(short (&map)[64][64], MachineBase *new_item);

	void add_item_to_map(short (&map)[64][64], MachineBase *new_item);

	void remove_item_from_map(short (&map)[64][64], MachineBase *item);

public slots:

	void placeItem(const int &n);

private:
	QMenu *menu;
	QGraphicsScene *scene;
	QSignalMapper *signalMapper;
};

#endif // CONSTRUCTIONBUTTON_H
