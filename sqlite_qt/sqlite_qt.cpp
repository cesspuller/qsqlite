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
                "name TEXT,"
                "gender TEXT,"
                "age INTEGER );" 
              );

   qDebug() << "ERROR:" << query->lastError().text();
   
   query->exec( 
                "CREATE TABLE IF NOT EXISTS products ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT,"
                "gender TEXT,"
                "FOREIGN KEY (id) REFERENCES customers(id) ON DELETE CASCADE )"  
              );

   qDebug() << "ERROR:" << query->lastError().text();
   
   query->exec( 
                "CREATE TABLE IF NOT EXISTS  orders ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "age INTEGER,"
                "FOREIGN KEY (age) REFERENCES customers(age) ON DELETE CASCADE );" 
              );

   qDebug() << "ERROR:" << query->lastError().text();

   //query->exec( 
   //             "CREATE TABLE departments ("
   //             "department_id INTEGER PRIMARY KEY AUTOINCREMENT,"
   //             "department_name VARCHAR );"
   //           );
   //
   //qDebug() << "ERROR:" << query->lastError().text();
   //
   //query->exec( 
   //             "CREATE TABLE employees ("
   //             "employee_id INTEGER PRIMARY KEY AUTOINCREMENT,"
   //             "last_name VARCHAR NOT NULL,"
   //             "first_name VARCHAR,"
   //             "department_id INTEGER,"
   //             "CONSTRAINT fk_departments"
   //             "FOREIGN KEY(department_id)"
   //             "REFERENCES departments( department_id )"
   //             "ON DELETE CASCADE );"
   //           );

   //query->exec( "CREATE TRIGGER insert_products "
   //             "AFTER INSERT ON departments "
   //             "BEGIN "
   //             "INSERT INTO employees (department_id ) "
   //             "VALUES (NEW.department_id ); "
   //             "END;" );

   query->exec( "PRAGMA foreign_keys = ON" );

   qDebug() << "ERROR:" << query->lastError().text();

   //query->exec( "CREATE TRIGGER IF NOT EXISTS insert_products "
   //             "AFTER INSERT ON customers "
   //             "BEGIN "
   //             "INSERT INTO products (name, gender) "
   //             "VALUES (NEW.name, NEW.gender); "
   //             "END;" );

   qDebug() << "ERROR:" << query->lastError().text();

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
   //ui.tableView_3->setModel( emailsModel );

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

   bool a = contactsModel->submitAll();

   qDebug() << "ERROR:" << contactsModel->lastError().text();
   qDebug() << "ERROR:" << query->lastError().text();
   qDebug() << "ERROR:" << dataBase.lastError().text();
   
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


      qDebug() << "ERROR:" << contactsModel->lastError().text();
      qDebug() << "ERROR:" << query->lastError().text();
      qDebug() << "ERROR:" << dataBase.lastError().text();
      //query->exec( "DELETE FROM customers WHERE id = 3" );
      //
      //qDebug() << "ERROR:" << query->lastError().text();
      //
      //auto f = elem.toString();
   }
};

void TMainWindow::qSelectedRow( const QItemSelection&, const QItemSelection& )
{
   selectedRows.clear();

   QModelIndexList selection = ui.tableView->selectionModel()->selectedIndexes();

   for ( auto& elem : selection )
   {
      //auto f = elem.data();
      selectedRows.push_back( elem.row() );
   }
};
