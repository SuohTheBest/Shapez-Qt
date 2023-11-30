#include "projdrill.h"
#include "./src/map/MapDisplayWidget.h"
#include "ui_projdrill.h"

projDrill::projDrill(QWidget *parent): QMainWindow(parent), ui(new Ui::projDrill)
{
    MapDisplayWidget *widget = new MapDisplayWidget(0,this);
    setCentralWidget(widget);
}
projDrill::~projDrill()
{
    delete ui;
}

