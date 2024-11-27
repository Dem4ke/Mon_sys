#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class Server : QTcpServer {
    Q_OBJECT

public:
    Server();

    QTcpSocket* socket;

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void clienDisconnected();
    void slotReadyRead();

private:
    void sentToClient(QString output);

private:
    QVector<QTcpSocket*> sockets_;
    QByteArray data_;

};

