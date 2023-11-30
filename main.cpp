#include "projdrill.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    projDrill w;
    w.show();
    return a.exec();
}
