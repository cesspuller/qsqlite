#include "TMainWindow.hpp"
#include <QtWidgets/QApplication>

int main( int argc, char* argv[] )
{
   QApplication a( argc, argv );
   TMainWindow w;

   w.show();

   return a.exec();
};
