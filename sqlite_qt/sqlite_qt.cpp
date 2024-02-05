#include "sqlite_qt.hpp"

TMainWindow::TMainWindow( QWidget* parent ) : QMainWindow( parent )
{
   ui.setupUi( this );
   dataBase = QSqlDatabase::addDatabase( "QSQLITE" );
   dataBase.setDatabaseName( "./testDB.db" );

   dataBase.open() ? qDebug( "open" ) : qDebug( "not open" );

   query = new QSqlQuery( dataBase );
   query->exec( "CREATE TABLE TelephoneBook( Firstname TEXT, Lastname TEXT, Telephone INT );" );

   qtable = new QSqlTableModel( this, dataBase );
   qtable->setTable( "TelephoneBook" );
   qtable->select();

   ui.tableView->setModel( qtable );

   connect( ui.pushButton_2, SIGNAL( clicked() ), this, 
                             SLOT( qAddEntry() ) );
   connect( ui.pushButton, SIGNAL( clicked() ), this, 
                           SLOT( qDeleteEntry() ) );
   
   connect( ui.tableView->selectionModel(), SIGNAL( selectionChanged( const QItemSelection&, const QItemSelection& ) ), this,
                                            SLOT( qSelectedRow( const QItemSelection&, const QItemSelection& ) ) );
};

void TMainWindow::qAddEntry()
{
   qtable->insertRow( qtable->rowCount() );
};

void TMainWindow::qDeleteEntry()
{
   buckUpDataBase = dataBase;

   for ( auto& elem : selectedRows )
   {
      qtable->removeRow( elem );
   }
};

void TMainWindow::qSelectedRow( const QItemSelection&, const QItemSelection& )
{
   selectedRows.clear();

   QModelIndexList selection = ui.tableView->selectionModel()->selectedIndexes();

   for ( auto& elem : selection )
   {
      selectedRows.insert( int( elem.row() ) );
   }
};
