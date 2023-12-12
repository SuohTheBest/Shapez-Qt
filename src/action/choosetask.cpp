#include "choosetask.h"
#include "ui_choosetask.h"

ChooseTask::ChooseTask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseTask)
{
    ui->setupUi(this);
    is_finished[0]=false;
    is_finished[1]=false;
    is_finished[2]=false;
    connect(ui->button_task1,&QPushButton::clicked,this,[this](){ handle_button_clicked(1); });
    connect(ui->button_task2,&QPushButton::clicked,this,[this](){ handle_button_clicked(2); });
    connect(ui->button_task3,&QPushButton::clicked,this,[this](){ handle_button_clicked(3); });
}

ChooseTask::~ChooseTask()
{
    delete ui;
}

void ChooseTask::set_finished(int n)
{
    is_finished[n]=true;
}

void ChooseTask::check_selectable() {
    if(!is_finished[0])ui->button_task1->setEnabled(true);
    else {
        ui->button_task1->setEnabled(false);
    }
    if(!is_finished[1])ui->button_task2->setEnabled(true);
    else {
        ui->button_task2->setEnabled(false);
    }
    if(!is_finished[2])ui->button_task3->setEnabled(true);
    else {
        ui->button_task3->setEnabled(false);
    }
}

void ChooseTask::handle_button_clicked(int n)
{
    emit send_task(n);
	close();
}
