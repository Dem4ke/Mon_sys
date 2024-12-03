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

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void clienDisconnected();
    void slotReadyRead();

private:
    void sendToClient(int flag, QVector<QString> output);

private:
    // Database users tools
    void addUser(QVector<QString> userInfo);
    void checkUserStatement(QVector<QString> userInfo);

private:
    // Database waters tools

private:
    quint16 blockSize_ = 0;             // Size of data package

    QTcpSocket* socket;
    QVector<QTcpSocket*> sockets_;      // Vector of "users" of server
    QByteArray data_;                   // Information byte array which server sents to client and get from it
};
}

/*  Flags to work with database is:
    1 - insert user in database
    2 - check user statement (is login and password are correct)
    3 - get info about water
*/
