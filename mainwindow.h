#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include "simconnectInterface/simconnectthread.h"
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum ConnectionState
    {
        CONNECTED,
        CONNECTING,
        DISCONNECTING,
        DISCONNECTED
    };

    std::atomic_bool sharedDataUpdated;
    QMutex sharedDataMutex;

    SharedDataStruct sharedData;

    SimconnectThread *simThread = nullptr;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void showSimMsg(const QString &msg);
    void quitFromSim();

    void simConnectFailed();
    void simConnected();

private slots:
    void newIncomingConnection();

    void clientDisconnected();

    void receivedDataFromClient();

    void readNewFlightplan();
    void clearFlightplan();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void initServer();

    void readFlightplan(const QString &fileName);

    void setSimConnectionState(ConnectionState state);
    void setClientConnectionState(ConnectionState state);

    void startSim(ActiveAirplaneSettings settings);
    void closeSim();

    void quitFromClient();

    void quitFromServer();

    ActiveAirplaneSettings readAircraftSettings();

    Ui::MainWindow *ui;
    QTcpServer tcpServer;
    QTcpSocket *tcpSocket;

};
#endif // MAINWINDOW_H
