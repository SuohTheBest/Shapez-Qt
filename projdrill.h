
#include "ui_projdrill.h"
#include <QMainWindow>
class projDrill:public QMainWindow
{
    Q_OBJECT
public:
    projDrill(QWidget *parent= nullptr);
    ~projDrill();
private:
    Ui::projDrill *ui;
};
