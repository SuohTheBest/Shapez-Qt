#include "choosetask.h"
#include "ui_choosetask.h"

bool ChooseTask::is_finished[3]={false,false,false};

ChooseTask::ChooseTask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseTask)
{
    ui->setupUi(this);
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
    ChooseTask::is_finished[n]=true;
}
bool ChooseTask::get_task(int n)
{
    return ChooseTask::is_finished[n];
}
void ChooseTask::check_selectable() {
    if(!ChooseTask::is_finished[0])ui->button_task1->setEnabled(true);
    else {
        ui->button_task1->setEnabled(false);
    }
    if(!ChooseTask::is_finished[1])ui->button_task2->setEnabled(true);
    else {
        ui->button_task2->setEnabled(false);
    }
    if(!ChooseTask::is_finished[2])ui->button_task3->setEnabled(true);
    else {
        ui->button_task3->setEnabled(false);
    }
}

void ChooseTask::handle_button_clicked(int n)
{
    emit send_task(n);
	close();
}

bool ChooseTask::has_new_task() {
	if(is_finished[0]&&is_finished[1]&&is_finished[2])return false;
	else return true;
}
