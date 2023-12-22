#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./src/map/MapCreator.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	menu = new MenuWidget(this);
	this->resize(1123, 855);
    setCentralWidget(menu);
    this->setWindowTitle("MyShapez");
    init();
	connect(menu, SIGNAL(game_start()), this, SLOT(start_game()));
	connect(menu, SIGNAL(game_load(short)), this, SLOT(load_game(short)));
}

MainWindow::~MainWindow() {
	delete ui;

}

void MainWindow::start_game() {
	disconnect(menu, SIGNAL(game_start()), this, SLOT(start_game()));
	disconnect(menu, SIGNAL(game_load(short)), this, SLOT(load_game(short)));
	menu->deleteLater();
	task = new ChooseTask();
    widget = new MapDisplayWidget(this);
	QRect deskRect = QApplication::desktop()->availableGeometry();
	this->move(deskRect.x(), deskRect.y());
	this->resize(deskRect.right() - deskRect.x(), deskRect.bottom() - deskRect.y());
	setCentralWidget(widget);
	connect(widget, SIGNAL(back_to_menu()), this, SLOT(back_to_menu()));
	connect(widget, SIGNAL(choose_task()), this, SLOT(choose_task()));
	connect(widget, SIGNAL(task_finished(int)), this, SLOT(handle_finished_task(int)));
}

void MainWindow::load_game(short chosen) {
	disconnect(menu, SIGNAL(game_start()), this, SLOT(start_game()));
	disconnect(menu, SIGNAL(game_load(short)), this, SLOT(load_game(short)));
	menu->deleteLater();
	task = new ChooseTask();
	widget = new MapDisplayWidget(chosen);
	QRect deskRect = QApplication::desktop()->availableGeometry();
	this->move(deskRect.x(), deskRect.y());
	this->resize(deskRect.right() - deskRect.x(), deskRect.bottom() - deskRect.y());
	setCentralWidget(widget);
	connect(widget, SIGNAL(back_to_menu()), this, SLOT(back_to_menu()));
	connect(widget, SIGNAL(choose_task()), this, SLOT(choose_task()));
	connect(widget, SIGNAL(task_finished(int)), this, SLOT(handle_finished_task(int)));
}

void MainWindow::back_to_menu() {
	widget->close();
	widget->deleteLater();
	this->resize(1123, 855);
	menu = new MenuWidget(this);
	connect(menu, SIGNAL(game_start()), this, SLOT(start_game()));
	connect(menu, SIGNAL(game_load(short)), this, SLOT(load_game(short)));
	setCentralWidget(menu);
}

void MainWindow::choose_task() {
	disconnect(task, SIGNAL(send_task(int)), widget, SLOT(set_task(int)));
	task->check_selectable();
	task->show();
	connect(task, SIGNAL(send_task(int)), widget, SLOT(set_task(int)));
}

void MainWindow::handle_finished_task(int n) {
	task->set_finished(n - 1);
}

void MainWindow::init() {
	if(access("./data",F_OK==-1))
	{
		mkdir("./data");
		mkdir("./data/savedata");
	}
	if (access("./data/savedata/save00", F_OK == -1)) {
		mkdir("./data/savedata/save00");
	}
	QString map_path("./data/savedata/save00/save.json");
	QFile map_save(map_path);
	if(!map_save.exists())
	{
		MapCreator* creator=new MapCreator();
		creator->createMap();
	}
	QString path("./data/savedata/save00/save.json");
	QFile save(path);
	if(!save.exists())
	{
		if (save.open(QIODevice::WriteOnly)) {
			QJsonObject root_obj;
			root_obj.insert("center_size",2);
			root_obj.insert("coal_num",10);
			root_obj.insert("gold_plus",0);
			root_obj.insert("gold",0);
			root_obj.insert("selection1_gold",75);
			root_obj.insert("selection2_gold",60);
			root_obj.insert("selection3_gold",50);
			QTextStream stream(&save);
			stream.setCodec("UTF-8");
			QJsonDocument doc;
			doc.setObject(root_obj);
			stream<<doc.toJson();
		} else {
			qDebug() << "Failed to create file.";
		}
	}
}

