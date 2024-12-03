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

public:
    // Database work tools
    bool connectToDatabase();
    //void isUserExists(QString login);

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void clienDisconnected();
    void slotReadyRead();

private:
    void sendToClient(QString output);

private:
    quint16 blockSize_ = 0;             // Size of data package

    QTcpSocket* socket;
    QVector<QTcpSocket*> sockets_;      // Vector of "users" of server
    QByteArray data_;                   // Information byte array which server sents to client and get from it
};
}
