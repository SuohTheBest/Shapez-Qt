#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menuwidget.h"
#include "./src/map/MapDisplayWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MenuWidget* menu=new MenuWidget(this);
    this->resize(1123,855);
    setCentralWidget(menu);
    connect(menu,SIGNAL(game_start()),this,SLOT(start_game()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_game()
{
    MapDisplayWidget* widget=new MapDisplayWidget(0,this);
    QRect deskRect = QApplication::desktop()->availableGeometry();
    widget->thread();
    this->move( deskRect.x(), deskRect.y() );
    this->resize( deskRect.right() - deskRect.x(), deskRect.bottom() - deskRect.y() );
    setCentralWidget(widget);
}
