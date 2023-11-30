
/********************************************************************************
** Form generated from reading UI file 'projdrill.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef PROJDRILL_H
#define PROJDRILL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_projDrill
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *projDrill)
    {
        if (projDrill->objectName().isEmpty())
            projDrill->setObjectName(QString::fromUtf8("projDrill"));
        projDrill->resize(800, 600);
        centralwidget = new QWidget(projDrill);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        projDrill->setCentralWidget(centralwidget);
        menubar = new QMenuBar(projDrill);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        projDrill->setMenuBar(menubar);
        statusbar = new QStatusBar(projDrill);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        projDrill->setStatusBar(statusbar);

        retranslateUi(projDrill);

        QMetaObject::connectSlotsByName(projDrill);
    } // setupUi

    void retranslateUi(QMainWindow *projDrill)
    {
        projDrill->setWindowTitle(QCoreApplication::translate("projDrill", "projDrill", nullptr));
    } // retranslateUi

};

namespace Ui {
    class projDrill: public Ui_projDrill {};
} // namespace Ui

QT_END_NAMESPACE

#endif
