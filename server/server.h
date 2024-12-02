#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

namespace MS {
class Server : QTcpServer {
    Q_OBJECT

public:
    Server();

    bool connectToDatabase();

    QTcpSocket* socket;

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void clienDisconnected();
    void slotReadyRead();

private:
    void sendToClient(QString output);

private:
    quint16 blockSize_ = 0;             // Size of data package

    QVector<QTcpSocket*> sockets_;      // Vector of "users" of server
    QByteArray data_;                   // Information byte array which server sents to client and get from it
};
}
