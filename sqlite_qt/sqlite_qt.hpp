#pragma once

#include <QtWidgets/QMainWindow>
#include <qmainwindow.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qsqltablemodel.h>
#include <qpushbutton.h>
#include "ui_sqlite_qt.h"
#include <set>

using namespace std;

class TMainWindow : public QMainWindow
{
   Q_OBJECT

   public:

   TMainWindow( QWidget* parent = nullptr );
   ~TMainWindow() = default;

   private slots:

   void qAddEntry();

   void qDeleteEntry();

   void qSelectedRow( const QItemSelection&, const QItemSelection& );
   
   private:

   Ui::sqlite_qtClass ui;

   QSqlDatabase dataBase;
   QSqlDatabase buckUpDataBase;

   QSqlQuery* query;
   QSqlTableModel* qtable;

   set<int> selectedRows;
};
