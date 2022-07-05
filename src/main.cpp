#include <QApplication>

#include "mainwindow/mainwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("MKootstra");
    a.setWindowIcon(QIcon("qrc:/SimconnectServerIcon.ico"));
    MainWindow w;
    w.show();
    return a.exec();
}
