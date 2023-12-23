#ifndef SAVEWIDGET_H
#define SAVEWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
	class SaveWidget;
}
/**
 * @brief 触发保存事件时弹出的窗口
 */
class SaveWidget : public QWidget {
Q_OBJECT

public:
	explicit SaveWidget(QWidget *parent = nullptr);

	void set_title(QString str);

	void check_is_selectable();

	~SaveWidget();

public slots:

	void button_clicked_1();

	void button_clicked_2();

	void button_clicked_3();

	void button_clicked_4();

signals:

	void send_data(short data_chosen);

private:
	Ui::SaveWidget *ui;
	short data_chosen;
};

#endif // SAVEWIDGET_H
