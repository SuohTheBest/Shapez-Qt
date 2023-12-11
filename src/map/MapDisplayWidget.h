#ifndef MAPDISPLAYWIDGET_H
#define MAPDISPLAYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QVector>
#include "QGraphicsPixmapItem"
#include "QGraphicsScene"
#include "QGraphicsView"
#include "QPixmap"
#include "QString"
#include "unistd.h"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QGroupBox"
#include "QTextEdit"
#include "MapBlockItem.h"
#include "../action/ConstructionButton.h"
#include "../action/RotateButton.h"
#include "../item/MachineShadow.h"
#include "../machine/MachineCenter.h"
#include "../action/SaveButton.h"

class MapDisplayWidget : public QWidget {
Q_OBJECT
public:
	MapDisplayWidget(int layer, QWidget *parent=nullptr);

	MapDisplayWidget(short save_chosen);

public slots:

	void pause();

	void restart();

protected:
	void handleSelectionChange();

private:
	int layer;
	short map_item_placed[64][64]={};//初始化应为-1
	short map[64][64]={};
	QList<MachineBase *> machine_placed;
	QGraphicsScene *scene;
	QGraphicsView *view;
	QHBoxLayout *layout_main;
	QVBoxLayout *layout_tools;
	QLabel *basic_info;
	QTextEdit *debug_message;
	ConstructionButton *construction_button;
	RotateButton *rotate_button;
	SaveButton *save_button;
	MachineShadow *shadow;
	MachineCenter *center;
};

#endif // MAPDISPLAYWIDGET_H
