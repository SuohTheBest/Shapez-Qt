#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("MyShapez");
    MainWindow projdrill;
    projdrill.show();
    return a.exec();
}
