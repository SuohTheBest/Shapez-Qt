#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./src/map/MapDisplayWidget.h"
#include "menuwidget.h"
#include "./src/action/choosetask.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);

	~MainWindow();

public slots:

	void start_game();

	void load_game(short chosen);

	void back_to_menu();

	void choose_task();

	void handle_finished_task(int n);

private:
	Ui::MainWindow *ui;
	MapDisplayWidget *widget;
	MenuWidget *menu;
	ChooseTask *task;
};

#endif // MAINWINDOW_H
