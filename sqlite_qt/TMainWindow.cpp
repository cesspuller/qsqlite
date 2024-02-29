#include "TMainWindow.hpp"

TMainWindow::TMainWindow( QWidget* parent ) : QMainWindow( parent )
{

   loger.SetLogPreferences( "./LogFile.txt", LogLevel::INFO, LogOutput::FILE );
   ui.setupUi( this );
   std::string log;

   dataBase = QSqlDatabase::addDatabase( "QSQLITE" );
   dataBase.setDatabaseName( "./testDB.db" );

   dataBase.open() ? qDebug( "Data base open" ) : qDebug( "Data base does not open" );

   query = new QSqlQuery( dataBase );


   error = query->exec(
                 "CREATE TABLE IF NOT EXISTS customers ("
                 "id INTEGER PRIMARY KEY AUTOINCREMENT"
                 "first_name TEXT NOT NULL,"
                 "last_name TEXT NOT NULL );"
              );

   if ( error ) loger.Log( 19, "Table 1 init success", LogLevel::INFO );
   else loger.Log( 19, query->lastError().text().toStdString(), LogLevel::INFO );

   error = query->exec(
                "CREATE TABLE IF NOT EXISTS products ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT NOT NULL,"
                "fk_customer_id INTEGER NOT NULL,"
                "FOREIGN KEY (fk_customer_id) REFERENCES customers(id) ON DELETE CASCADE )"  
              );
   
   if ( error ) loger.Log( 29, "Table 2 creation success", LogLevel::INFO );
   else loger.Log( 29, query->lastError().text().toStdString(), LogLevel::INFO );

   error = query->exec(
                "CREATE TABLE IF NOT EXISTS orders ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "city TEXT NOT NULL,"
                "fk_customer_id INTEGER NOT NULL,"
                "FOREIGN KEY (fk_customer_id) REFERENCES customers(id) ON DELETE CASCADE );" 
              );

   if ( error ) loger.Log( 40, "Table 3 creation success", LogLevel::INFO );
   else loger.Log( 40, query->lastError().text().toStdString(), LogLevel::INFO );

   query->exec( "PRAGMA foreign_keys = ON" );

   contactsModel = new QSqlTableModel( this, dataBase );
   contactsModel->setTable( "customers" );
   contactsModel->select();

   cityOrderModel = new QSqlTableModel( this, dataBase );
   cityOrderModel->setTable( "products" );
   cityOrderModel->select();

   productModel = new QSqlTableModel( this, dataBase );
   productModel->setTable( "orders" );
   productModel->select();

   ui.tableView->setModel( contactsModel );
   ui.tableView_2->setModel( cityOrderModel );
   ui.tableView_3->setModel( productModel );

   connect( ui.pushButton_2, SIGNAL( clicked() ), this, 
                             SLOT( qAddEntry( ) ) );
   
   connect( ui.pushButton, SIGNAL( clicked() ), this, 
                           SLOT( qDeleteEntry() ) );
   
   connect( ui.tableView->selectionModel(), SIGNAL( selectionChanged( const QItemSelection&, const QItemSelection& ) ), this,
                                            SLOT( qSelectedRow( const QItemSelection&, const QItemSelection& ) ) );
};

void TMainWindow::qAddEntry()
{
   error = contactsModel->insertRow( contactsModel->rowCount() );

   if (error) loger.Log( 78, "Row insert OK", LogLevel::DEBUG );
   else loger.Log( 78, contactsModel->lastError().text().toStdString(), LogLevel::DEBUG );

   error = cityOrderModel->insertRow( cityOrderModel->rowCount() );

   if ( error ) loger.Log( 85, "Row insert OK", LogLevel::DEBUG );
   else loger.Log( 85, cityOrderModel->lastError().text().toStdString(), LogLevel::DEBUG );

   error = productModel->insertRow( productModel->rowCount() );

   if ( error ) loger.Log( 90, "Row insert OK", LogLevel::DEBUG );
   else loger.Log( 90, cityOrderModel->lastError().text().toStdString(), LogLevel::DEBUG );
};

void TMainWindow::qDeleteEntry()
{
   for ( auto& elem : selectedRows )
   {
      error = contactsModel->removeRow( elem );

      if ( error ) loger.Log( 100, "Row delete OK", LogLevel::DEBUG );
      else loger.Log( 100, contactsModel->lastError().text().toStdString(), LogLevel::DEBUG );
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
                        

