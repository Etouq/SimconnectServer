#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ConnectionHandler/ConnectionHandler.hpp"

#include <QMainWindow>
#include <QString>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

    ConnectionHandler d_connectionHandler;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setSimConnectionState(ConnectionHandler::ConnectionState state);
    void setClientConnectionState(ConnectionHandler::ConnectionState state);

    void readNewFlightplan();
    void clearFlightplan();

    void updateNetworkData(const QHostAddress &address, quint16 port);

private:

    void readFlightplan(const QString &fileName);



};
#endif   // MAINWINDOW_H
