#include "../mainwindow.h"
#include "../ui_mainwindow.h"

#include <QMessageBox>
#include <QNetworkInterface>

void MainWindow::initServer()
{
    if (!tcpServer.listen(QHostAddress::Any, 42069))   // epic meme number lol
        if (!tcpServer.listen())
        {
            QMessageBox::critical(this,
                                  "Simconnect Server",
                                  "Unable to start the server: " + tcpServer.errorString() + ".");
            return;
        }


    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // use the first non-loopback ipv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (!ipAddressesList.at(i).isLoopback()
            && ipAddressesList.at(i).protocol() == QAbstractSocket::IPv4Protocol)
        {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use first non-loopback
    if (ipAddress.isEmpty())
        for (int i = 0; i < ipAddressesList.size(); ++i)
        {
            if (!ipAddressesList.at(i).isLoopback())
            {
                ipAddress = ipAddressesList.at(i).toString();
                break;
            }
        }
    // else use localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    ui->addressLabel->setText(ipAddress);
    ui->portLabel->setText(QString::number(tcpServer.serverPort()));

    QString tooltipText = "Also Available:";
    QString ipv4List;
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (!ipAddressesList.at(i).isLoopback()
            && ipAddressesList.at(i).protocol() == QAbstractSocket::IPv4Protocol)
        {
            ipv4List += "\n" + ipAddressesList.at(i).toString();
        }
    }

    QString ipv6List;
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (!ipAddressesList.at(i).isLoopback()
            && ipAddressesList.at(i).protocol() == QAbstractSocket::IPv6Protocol)
        {
            ipv6List += "\n" + ipAddressesList.at(i).toString();
        }
    }

    QString loopbackList;
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i).isLoopback())
        {
            loopbackList += "\n" + ipAddressesList.at(i).toString();
        }
    }
    if (!ipv4List.isEmpty())
        tooltipText += "\nIPv4:" + ipv4List;
    if (!ipv6List.isEmpty())
        tooltipText += "\nIPv6:" + ipv6List;
    if (!loopbackList.isEmpty())
        tooltipText += "\nLoopback:" + loopbackList;

    ui->addressLabel->setToolTip(tooltipText);
    ui->addressLabel->setToolTipDuration(INT_MAX);
}
