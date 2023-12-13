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
#include "../action/PauseButton.h"
#include "../action/BackToMenu.h"
#include "../action/levelup.h"
#include "../machine/MachineCutter.h"
#include "../machine/MachineDriller.h"
#include "../action/DeleteButton.h"

class MapDisplayWidget : public QWidget {
Q_OBJECT
public:
	MapDisplayWidget(QWidget *parent = nullptr);

	MapDisplayWidget(short save_chosen);

	float driller_speed_multiplier = 1;
	float conveyer_speed_multiplier = 1;
	float cutter_speed_multiplier = 1;

public slots:

	void handle_pause_button_clicked();

	void handle_back_button_clicked();

	void handle_task_finished(int n);

	void set_task(int n);

	void level_up(int n);

	void pause();

	void restart();

signals:

	void back_to_menu();

	void choose_task();

	void task_finished(int n);

protected:
	void handleSelectionChange();

private:
	void read_global_levelup();
	int center_size;
	int gold;
	int gold_plus;
	short map_item_placed[64][64] = {};//初始化应为-1
	short map[64][64] = {};
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
	PauseButton *pause_button;
	BackToMenuButton *back_button;
	DeleteButton *delete_button;
	MachineShadow *shadow;
	MachineCenter *center;
	MachineBase* delete_machine;
};

#endif // MAPDISPLAYWIDGET_H
