#include "menuwidget.h"
#include "ui_menuwidget.h"
#include "./src/action/savewidget.h"
MenuWidget::MenuWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::MenuWidget) {
    ui->setupUi(this);
    connect(ui->button_start_game, SIGNAL(clicked()),this,SLOT(start_game()));
    connect(ui->button_exit,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(ui->button_load_game,SIGNAL(clicked()),this,SLOT(load_game()));
    this->resize(1123,855);

}

MenuWidget::~MenuWidget() {
    delete ui;
}

void MenuWidget::start_game()
{
    emit game_start();
}

void MenuWidget::load_game()
{
    SaveWidget* savewidget=new SaveWidget();
    savewidget->check_is_selectable();
    savewidget->show();
    connect(savewidget,SIGNAL(send_data(short)),this,SLOT(load_game_selected(short)));
}

void MenuWidget::load_game_selected(short chosen)
{
    emit game_load(chosen);
}
