#pragma once

#include <QTcpSocket>

namespace MS {
class Socket : QTcpSocket {
    Q_OBJECT

public:
    Socket();

    // Users tools
    void checkUserStatement(std::vector<QString>& userInfo);
    void addUser(std::vector<QString>& userInfo);

    bool isUserExists();

private:
    bool isUserExists_ = false;

public slots:
    // Server tools
    void slotReadyRead();

private:
    // Принимать все равно одно что-то, нужно подумать, возможно флаг нужно будет передать
    void sendToServer(QString output);
    void sendToServer(QVector<QString> output);

private:
    quint16 blockSize_ = 0;         // Size of data package
    QString input_;                 // Information from server

    QTcpSocket* socket_;            // Socket to get/put info from/to server
    QByteArray data_;               // Variable which uses to store relocates data
};
}
