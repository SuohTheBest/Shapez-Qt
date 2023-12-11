#include "menuwidget.h"
#include "ui_menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent) :
		QWidget(parent), ui(new Ui::MenuWidget) {
	ui->setupUi(this);
    connect(ui->button_start_game, SIGNAL(clicked()),this,SLOT(start_game()));
    connect(ui->button_exit,SIGNAL(clicked()),qApp,SLOT(quit()));
    this->resize(1123,855);

}

MenuWidget::~MenuWidget() {
	delete ui;
}

void MenuWidget::start_game()
{

    emit game_start();
}
