#include "mainwindow.hpp"

#include <QCloseEvent>
#include <QSysInfo>
#include <QHostInfo>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    ui(new Ui::MainWindow),
    d_connectionHandler(this)
{
    ui->setupUi(this);


    connect(ui->clearFpButton, &QPushButton::pressed, this, &MainWindow::clearFlightplan);
    connect(ui->readNewFpButton, &QPushButton::pressed, this, &MainWindow::readNewFlightplan);

    connect(&d_connectionHandler,
            &ConnectionHandler::simConnectionStateChanged,
            this,
            &MainWindow::setSimConnectionState);
    connect(&d_connectionHandler,
            &ConnectionHandler::clienConnectionStateChanged,
            this,
            &MainWindow::setClientConnectionState);
    connect(&d_connectionHandler,
            &ConnectionHandler::networkChanged,
            this,
            &MainWindow::updateNetworkData);

    d_connectionHandler.init();

    adjustSize();

    qDebug() << "machine host name:" << QSysInfo::machineHostName();
    qDebug() << "machine unique id:" << QSysInfo::machineUniqueId();
    qDebug() << "pretty product name:" << QSysInfo::prettyProductName();
    qDebug() << "local domain name:" << QHostInfo::localDomainName();
    qDebug() << "local host name:" << QHostInfo::localHostName();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateNetworkData(const QHostAddress &address, quint16 port)
{
    ui->addressLabel->setText(address.toString());
    ui->portLabel->setText(QString::number(port));
}

void MainWindow::setSimConnectionState(ConnectionHandler::ConnectionState state)
{
    switch (state)
    {
        case ConnectionHandler::ConnectionState::CONNECTED:
            ui->simConnectionState->setStyleSheet(
              "color: white;border-radius: 11;background-color: qlineargradient(spread:pad, "
              "x1:0.145, y1:0.16, x2:1, y2:1, "
              "stop:0 rgba(20, 252, 7, 255), stop:1 rgba(25, 134, 5, 255));");
            break;
        case ConnectionHandler::ConnectionState::CONNECTING:
        case ConnectionHandler::ConnectionState::DISCONNECTING:
            ui->simConnectionState->setStyleSheet(
              "color: white;border-radius: 11;background-color: qlineargradient(spread:pad, "
              "x1:0.232, y1:0.272, x2:0.98, "
              "y2:0.959773, stop:0 rgba(255, 113, 4, 255), stop:1 rgba(91, 41, 7, 255));");
            break;
        case ConnectionHandler::ConnectionState::DISCONNECTED:
            ui->simConnectionState->setStyleSheet(
              "color: white;border-radius: 11;background-color: qlineargradient(spread:pad, "
              "x1:0.145, y1:0.16, x2:0.92, "
              "y2:0.988636, stop:0 rgba(255, 12, 12, 255), stop:0.869347 rgba(103, 0, 0, 255));");
            break;
    }
}

void MainWindow::setClientConnectionState(ConnectionHandler::ConnectionState state)
{
    switch (state)
    {
        case ConnectionHandler::ConnectionState::CONNECTED:
            ui->clientConnectionState->setStyleSheet(
              "color: white;border-radius: 11;background-color: qlineargradient(spread:pad, "
              "x1:0.145, y1:0.16, x2:1, "
              "y2:1, stop:0 rgba(20, 252, 7, 255), stop:1 rgba(25, 134, 5, 255));");

            ui->clearFpButton->setDisabled(false);
            ui->readNewFpButton->setDisabled(false);
            break;
        case ConnectionHandler::ConnectionState::CONNECTING:
        case ConnectionHandler::ConnectionState::DISCONNECTING:
            ui->clientConnectionState->setStyleSheet(
              "color: white;border-radius: 11;background-color: qlineargradient(spread:pad, "
              "x1:0.232, y1:0.272, "
              "x2:0.98, y2:0.959773, stop:0 rgba(255, 113, 4, 255), stop:1 rgba(91, 41, 7, 255));");
            break;
        case ConnectionHandler::ConnectionState::DISCONNECTED:
            ui->clientConnectionState->setStyleSheet(
              "color: white;border-radius: 11;background-color: qlineargradient(spread:pad, "
              "x1:0.145, y1:0.16, x2:0.92, "
              "y2:0.988636, stop:0 rgba(255, 12, 12, 255), stop:0.869347 rgba(103, 0, 0, 255));");

            ui->clearFpButton->setDisabled(true);
            ui->readNewFpButton->setDisabled(true);
            break;
    }
}
