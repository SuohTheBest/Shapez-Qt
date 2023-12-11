#include "savewidget.h"
#include "ui_savewidget.h"

SaveWidget::SaveWidget(QWidget *parent) :
		QWidget(parent), ui(new Ui::SaveWidget) {
	ui->setupUi(this);
    this->data_chosen=0;
    connect(ui->button_data1,SIGNAL(clicked()),this,SLOT(button_clicked_1()));
    connect(ui->button_data2,SIGNAL(clicked()),this,SLOT(button_clicked_2()));
    connect(ui->button_data3,SIGNAL(clicked()),this,SLOT(button_clicked_3()));
    connect(ui->button_data4,SIGNAL(clicked()),this,SLOT(button_clicked_4()));
}

SaveWidget::~SaveWidget() {
	delete ui;
}

void SaveWidget::button_clicked_1()
{
    data_chosen=1;
    emit send_data(data_chosen);
    close();
}

void SaveWidget::button_clicked_2()
{
    data_chosen=2;
    emit send_data(data_chosen);
    close();
}

void SaveWidget::button_clicked_3()
{
    data_chosen=3;
    emit send_data(data_chosen);
    close();
}

void SaveWidget::button_clicked_4()
{
    data_chosen=4;
    emit send_data(data_chosen);
    close();
}
