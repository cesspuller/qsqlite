#include "sqlite_qt.hpp"

TMainWindow::TMainWindow( QWidget* parent ) : QMainWindow( parent )
{
   ui.setupUi( this );
   dataBase = QSqlDatabase::addDatabase( "QSQLITE" );
   dataBase.setDatabaseName( "./testDB.db" );

   dataBase.open() ? qDebug( "open" ) : qDebug( "not open" );

   query = new QSqlQuery( dataBase );

   query->exec( 
                "CREATE TABLE IF NOT EXISTS customers ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT NOT NULL,"
                "gender TEXT NOT NULL,"
                "age INTEGER NOT NULL );" 
              );

   query->exec( 
                "CREATE TABLE IF NOT EXISTS products ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT NOT NULL,"
                "gender TEXT NOT NULL,"
                "FOREIGN KEY (id) REFERENCES customers(id) ON DELETE CASCADE )"  
              );
   
   query->exec( 
                "CREATE TABLE IF NOT EXISTS  orders ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "age INTEGER NOT NULL,"
                "FOREIGN KEY (id) REFERENCES customers(id) ON DELETE CASCADE );" 
              );

   query->exec( "PRAGMA foreign_keys = ON" );

   contactsModel = new QSqlRelationalTableModel( this, dataBase );
   contactsModel->setTable( "customers" );
   contactsModel->select();

   phoneNumbersModel = new QSqlRelationalTableModel( this, dataBase );
   phoneNumbersModel->setTable( "products" );
   phoneNumbersModel->select();

   emailsModel = new QSqlRelationalTableModel( this, dataBase );
   emailsModel->setTable( "orders" );
   emailsModel->select();

   ui.tableView->setModel( contactsModel );
   ui.tableView_2->setModel( phoneNumbersModel );
   ui.tableView_3->setModel( emailsModel );

   connect( ui.pushButton_2, SIGNAL( clicked() ), this, 
                             SLOT( qAddEntry( ) ) );
   
   connect( ui.pushButton, SIGNAL( clicked() ), this, 
                           SLOT( qDeleteEntry() ) );
   
   connect( ui.tableView->selectionModel(), SIGNAL( selectionChanged( const QItemSelection&, const QItemSelection& ) ), this,
                                            SLOT( qSelectedRow( const QItemSelection&, const QItemSelection& ) ) );
};

void TMainWindow::qAddEntry()
{
   contactsModel->insertRow( contactsModel->rowCount() );
   phoneNumbersModel->insertRow( phoneNumbersModel->rowCount() );
   emailsModel->insertRow( emailsModel->rowCount() );
};

void TMainWindow::qDeleteEntry()
{
   for ( auto& elem : selectedRows )
   {
      contactsModel->removeRow( elem );

      ui.tableView_2->repaint();
      ui.tableView_3->repaint();
      //qDebug() << "ERROR:" << phoneNumbersModel->lastError().text();
   }
};

void TMainWindow::qSelectedRow( const QItemSelection&, const QItemSelection& )
{
   selectedRows.clear();

   QModelIndexList selection = ui.tableView->selectionModel()->selectedIndexes();

   for ( auto& elem : selection )
   {
      selectedRows.push_back( elem.row() );
   }
};

