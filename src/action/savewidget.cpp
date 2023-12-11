#include "savewidget.h"
#include "QFile"
#include "ui_savewidget.h"

SaveWidget::SaveWidget(QWidget *parent) :
		QWidget(parent), ui(new Ui::SaveWidget) {
	ui->setupUi(this);
	this->data_chosen = 0;
	connect(ui->button_data1, SIGNAL(clicked()), this, SLOT(button_clicked_1()));
	connect(ui->button_data2, SIGNAL(clicked()), this, SLOT(button_clicked_2()));
	connect(ui->button_data3, SIGNAL(clicked()), this, SLOT(button_clicked_3()));
	connect(ui->button_data4, SIGNAL(clicked()), this, SLOT(button_clicked_4()));
}

SaveWidget::~SaveWidget() {
	delete ui;
}

void SaveWidget::button_clicked_1() {
	data_chosen = 1;
	emit send_data(data_chosen);
	close();
}

void SaveWidget::button_clicked_2() {
	data_chosen = 2;
	emit send_data(data_chosen);
	close();
}

void SaveWidget::button_clicked_3() {
	data_chosen = 3;
	emit send_data(data_chosen);
	close();
}

void SaveWidget::button_clicked_4() {
	data_chosen = 4;
	emit send_data(data_chosen);
	close();
}

void SaveWidget::set_title(QString str) {
	ui->title->setText(str);
}

void SaveWidget::check_is_selectable() {
	QString file_name=QString::fromStdString("./data/savedata/save01/data.json");
	QFile save_file_1(file_name);
	if (!save_file_1.open(QIODevice::ReadOnly)) {
        ui->button_data1->setEnabled(false);
	}
    else {
        ui->button_data1->setEnabled(true);
		save_file_1.close();
    }
	file_name=QString::fromStdString("./data/savedata/save02/data.json");
	QFile save_file_2(file_name);
	if (!save_file_2.open(QIODevice::ReadOnly)) {
		ui->button_data2->setEnabled(false);
	}
	else {
		ui->button_data2->setEnabled(true);
		save_file_2.close();
	}
	file_name=QString::fromStdString("./data/savedata/save03/data.json");
	QFile save_file_3(file_name);
	if (!save_file_3.open(QIODevice::ReadOnly)) {
		ui->button_data3->setEnabled(false);
	}
	else {
		ui->button_data3->setEnabled(true);
		save_file_3.close();
	}
	file_name=QString::fromStdString("./data/savedata/save04/data.json");
	QFile save_file_4(file_name);
	if (!save_file_4.open(QIODevice::ReadOnly)) {
		ui->button_data4->setEnabled(false);
	}
	else {
		ui->button_data4->setEnabled(true);
		save_file_4.close();
	}
}
