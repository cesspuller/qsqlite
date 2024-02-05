#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sqlite_qt.h"

class sqlite_qt : public QMainWindow
{
    Q_OBJECT

public:
    sqlite_qt(QWidget *parent = nullptr);
    ~sqlite_qt();

private:
    Ui::sqlite_qtClass ui;
};
