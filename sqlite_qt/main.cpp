#include "sqlite_qt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sqlite_qt w;
    w.show();
    return a.exec();
}
