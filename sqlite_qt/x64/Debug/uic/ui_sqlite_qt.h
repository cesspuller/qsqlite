/********************************************************************************
** Form generated from reading UI file 'sqlite_qt.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SQLITE_QT_H
#define UI_SQLITE_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sqlite_qtClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *sqlite_qtClass)
    {
        if (sqlite_qtClass->objectName().isEmpty())
            sqlite_qtClass->setObjectName("sqlite_qtClass");
        sqlite_qtClass->resize(600, 400);
        menuBar = new QMenuBar(sqlite_qtClass);
        menuBar->setObjectName("menuBar");
        sqlite_qtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(sqlite_qtClass);
        mainToolBar->setObjectName("mainToolBar");
        sqlite_qtClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(sqlite_qtClass);
        centralWidget->setObjectName("centralWidget");
        sqlite_qtClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(sqlite_qtClass);
        statusBar->setObjectName("statusBar");
        sqlite_qtClass->setStatusBar(statusBar);

        retranslateUi(sqlite_qtClass);

        QMetaObject::connectSlotsByName(sqlite_qtClass);
    } // setupUi

    void retranslateUi(QMainWindow *sqlite_qtClass)
    {
        sqlite_qtClass->setWindowTitle(QCoreApplication::translate("sqlite_qtClass", "sqlite_qt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sqlite_qtClass: public Ui_sqlite_qtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQLITE_QT_H
