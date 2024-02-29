#ifndef _T_MAIN_WINDOW_HPP_
#define _T_MAIN_WINDOW_

#include <QtWidgets/QMainWindow>
#include <qmainwindow.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qsqlerror.h>
#include <qsqltablemodel>
#include <qpushbutton.h>
#include "ui_sqlite_qt.h"
#include "TLogger.hpp"

#include <vector>
#include <iostream>
#include <fstream> 

class TMainWindow : public QMainWindow
{
   Q_OBJECT

   public:

      TMainWindow( QWidget* parent = nullptr );
      ~TMainWindow() = default;

   private slots:

      //! ‘ункци€-слот дл€ добавлени€ новой €чейки в бд 
      void qAddEntry();

      //! ‘ункци€-слот дл€ удалени€ €чейки из бд 
      void qDeleteEntry();

      //! ‘ункци€-слот дл€ отслеживани€ выбраных €чеек в текущий момент
      void qSelectedRow( const QItemSelection&, const QItemSelection& );

   private:

      Ui::sqlite_qtClass ui;
      QSqlDatabase dataBase;
      QSqlQuery* query;

      QSqlTableModel* contactsModel;
      QSqlTableModel* cityOrderModel;
      QSqlTableModel* productModel;
      Logger loger;
      std::vector<int> selectedRows;

      bool error;
};

#endif // !_T_MAIN_WINDOW_HPP_