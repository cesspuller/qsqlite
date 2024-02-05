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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sqlite_qtClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTableView *tableView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *sqlite_qtClass)
    {
        if (sqlite_qtClass->objectName().isEmpty())
            sqlite_qtClass->setObjectName("sqlite_qtClass");
        sqlite_qtClass->resize(624, 456);
        centralWidget = new QWidget(sqlite_qtClass);
        centralWidget->setObjectName("centralWidget");
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 2, 1, 1, 1);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout->addWidget(pushButton_2, 2, 0, 1, 1);

        tableView = new QTableView(centralWidget);
        tableView->setObjectName("tableView");

        gridLayout->addWidget(tableView, 0, 0, 1, 2);

        sqlite_qtClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(sqlite_qtClass);
        mainToolBar->setObjectName("mainToolBar");
        sqlite_qtClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(sqlite_qtClass);
        statusBar->setObjectName("statusBar");
        sqlite_qtClass->setStatusBar(statusBar);

        retranslateUi(sqlite_qtClass);

        QMetaObject::connectSlotsByName(sqlite_qtClass);
    } // setupUi

    void retranslateUi(QMainWindow *sqlite_qtClass)
    {
        sqlite_qtClass->setWindowTitle(QCoreApplication::translate("sqlite_qtClass", "sqlite_qt", nullptr));
        pushButton->setText(QCoreApplication::translate("sqlite_qtClass", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        pushButton_2->setText(QCoreApplication::translate("sqlite_qtClass", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sqlite_qtClass: public Ui_sqlite_qtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQLITE_QT_H
