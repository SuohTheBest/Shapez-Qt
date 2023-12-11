#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow projdrill;
    projdrill.show();
    return a.exec();
}
