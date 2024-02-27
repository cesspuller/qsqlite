#include "sqlite_qt.hpp"

TMainWindow::TMainWindow( QWidget* parent ) : QMainWindow( parent )
{
   ui.setupUi( this );
   dataBase = QSqlDatabase::addDatabase( "QSQLITE" );
   dataBase.setDatabaseName( "./testDB.db" );

   dataBase.open() ? qDebug( "open" ) : qDebug( "not open" );

   query = new QSqlQuery( dataBase );

   query->exec( "CREATE TABLE customers ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT,"
                "gender TEXT,"
                "age INTEGER );" );

   query->exec( "CREATE TABLE products ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT,"
                "gender TEXT,"
                "FOREIGN KEY (id) REFERENCES customers(id) ON DELETE CASCADE )"  );

   query->exec( "CREATE TABLE orders ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "age INTEGER,"
                "FOREIGN KEY (age) REFERENCES customers(age) ON DELETE CASCADE );" );

   //query->exec( "PRAGMA foreign_keys = ON" );

   query->exec( "CREATE TRIGGER insert_products "
                "AFTER INSERT ON customers "
                "BEGIN "
                "INSERT INTO products (name, gender) "
                "VALUES (NEW.name, NEW.gender); "
                "END;" );

   contactsModel = new QSqlRelationalTableModel( this, dataBase );
   contactsModel->setTable( "customers" );
   //contactsModel->setEditStrategy( QSqlTableModel::OnFieldChange );
   contactsModel->select();

   phoneNumbersModel = new QSqlRelationalTableModel( this, dataBase );
   phoneNumbersModel->setTable( "products" );
   //phoneNumbersModel->setEditStrategy( QSqlTableModel::OnFieldChange );
   phoneNumbersModel->select();

   emailsModel = new QSqlRelationalTableModel( this, dataBase );
   emailsModel->setTable( "orders" );
   //emailsModel->setEditStrategy( QSqlTableModel::OnFieldChange );
   //emailsModel->setRelation( 1, QSqlRelation( "customers", "id", "name" ) );
   //emailsModel->setRelation( 2, QSqlRelation( "products", "id", "name" ) );
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

   qDebug() << "Error inserting into customers table:" << dataBase.lastError().text();
};

void TMainWindow::qAddEntry()
{
   contactsModel->insertRow( contactsModel->rowCount() );
   
   //if ( !contactsModel->submitAll() ) 
   //{
   //   qDebug() << "Error inserting into customers table:" << contactsModel->lastError().text();
   //}
   //else 
   //{
   //   qDebug() << "Customer added successfully";
   //}
};

void TMainWindow::qDeleteEntry()
{
   for ( auto& elem : selectedRows )
   {
      contactsModel->removeRow( elem );
   }
};

void TMainWindow::qSelectedRow( const QItemSelection&, const QItemSelection& )
{
   selectedRows.clear();

   QModelIndexList selection = ui.tableView->selectionModel()->selectedIndexes();

   for ( auto& elem : selection )
   {
      selectedRows.push_back( int( elem.row() ) );
   }
};
