#ifndef CHOOSETASK_H
#define CHOOSETASK_H

#include <QWidget>

namespace Ui {
	class ChooseTask;
}
/**
 * @brief 选择任务的弹出窗口
 */
class ChooseTask : public QWidget {
Q_OBJECT

public:
	explicit ChooseTask(QWidget *parent = nullptr);

	void set_finished(int n);

	void check_selectable();

	bool has_new_task();

    static bool get_task(int n);

	~ChooseTask();

	static bool is_finished[3];
public slots:
    void handle_button_clicked(int n);

signals:
    void send_task(int n);

private:
	Ui::ChooseTask *ui;
};

#endif // CHOOSETASK_H
