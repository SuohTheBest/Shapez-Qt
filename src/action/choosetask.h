#ifndef CHOOSETASK_H
#define CHOOSETASK_H

#include <QWidget>

namespace Ui {
	class ChooseTask;
}

class ChooseTask : public QWidget {
Q_OBJECT

public:
	explicit ChooseTask(QWidget *parent = nullptr);

	void set_finished(int n);

	void check_selectable();

	~ChooseTask();

	bool is_finished[3];
public slots:
    void handle_button_clicked(int n);

signals:
    void send_task(int n);

private:
	Ui::ChooseTask *ui;
};

#endif // CHOOSETASK_H
