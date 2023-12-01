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

class MapDisplayWidget : public QWidget {
Q_OBJECT
public:
	MapDisplayWidget(int layer, QWidget *parent);

protected:
	void keyPressEvent(QKeyEvent *event) override;

	void mousePressEvent(QMouseEvent *event) override;

	void handleSelectionChange();

private:
	int layer;
	short map_item_placed[64][64];
	QList<MachineBase *> machine_placed;
	QGraphicsScene *scene;
	QGraphicsView *view;
	QHBoxLayout *layout_main;
	QVBoxLayout *layout_tools;
	QLabel *basic_info;
	QTextEdit *debug_message;
	ConstructionButton *construction_button;
	RotateButton *rotate_button;
	MachineShadow *shadow;
};

#endif // MAPDISPLAYWIDGET_H
