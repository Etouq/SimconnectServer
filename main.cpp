#include <QApplication>

#include "mainwindow/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("MKootstra");
    a.setWindowIcon(QIcon(":/SimconnectServerIcon.ico"));
    MainWindow w;
    w.show();
    return a.exec();
}
