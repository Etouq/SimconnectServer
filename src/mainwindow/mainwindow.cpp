#include "mainwindow.hpp"

#include "FlightplanReader/flightplanreader.hpp"
#include "common/dataIdentifiers.hpp"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QNetworkInterface>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow), tcpSocket(new QTcpSocket)
{
    ui->setupUi(this);

    connect(&tcpServer, &QTcpServer::newConnection, this, &MainWindow::newIncomingConnection);

    connect(ui->clearFpButton, &QPushButton::pressed, this, &MainWindow::clearFlightplan);
    connect(ui->readNewFpButton, &QPushButton::pressed, this, &MainWindow::readNewFlightplan);

    initServer();

    adjustSize();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tcpSocket;
    delete simThread;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (simThread != nullptr && simThread->isRunning())
        closeSim();

    tcpSocket->abort();
    tcpServer.close();

    event->accept();
}


void MainWindow::setSimConnectionState(ConnectionState state)
{
    switch (state)
    {
        case CONNECTED:
            ui->simConnectionState->setStyleSheet(
              "color: white;border-radius: 11;background-color: qlineargradient(spread:pad, "
              "x1:0.145, y1:0.16, x2:1, y2:1, "
              "stop:0 rgba(20, 252, 7, 255), stop:1 rgba(25, 134, 5, 255));");
            break;
        case CONNECTING:
        case DISCONNECTING:
            ui->simConnectionState->setStyleSheet(
              "color: white;border-radius: 11;background-color: qlineargradient(spread:pad, "
              "x1:0.232, y1:0.272, x2:0.98, "
              "y2:0.959773, stop:0 rgba(255, 113, 4, 255), stop:1 rgba(91, 41, 7, 255));");
            break;
        case DISCONNECTED:
            ui->simConnectionState->setStyleSheet(
              "color: white;border-radius: 11;background-color: qlineargradient(spread:pad, "
              "x1:0.145, y1:0.16, x2:0.92, "
              "y2:0.988636, stop:0 rgba(255, 12, 12, 255), stop:0.869347 rgba(103, 0, 0, 255));");
            break;
    }
}

void MainWindow::setClientConnectionState(ConnectionState state)
{
    switch (state)
    {
        case CONNECTED:
            ui->clientConnectionState->setStyleSheet(
              "color: white;border-radius: 11;background-color: qlineargradient(spread:pad, "
              "x1:0.145, y1:0.16, x2:1, "
              "y2:1, stop:0 rgba(20, 252, 7, 255), stop:1 rgba(25, 134, 5, 255));");
            break;
        case CONNECTING:
        case DISCONNECTING:
            ui->clientConnectionState->setStyleSheet(
              "color: white;border-radius: 11;background-color: qlineargradient(spread:pad, "
              "x1:0.232, y1:0.272, "
              "x2:0.98, y2:0.959773, stop:0 rgba(255, 113, 4, 255), stop:1 rgba(91, 41, 7, 255));");
            break;
        case DISCONNECTED:
            ui->clientConnectionState->setStyleSheet(
              "color: white;border-radius: 11;background-color: qlineargradient(spread:pad, "
              "x1:0.145, y1:0.16, x2:0.92, "
              "y2:0.988636, stop:0 rgba(255, 12, 12, 255), stop:0.869347 rgba(103, 0, 0, 255));");
            break;
    }
}
