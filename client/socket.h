#pragma once

#include <QTcpSocket>

namespace MS {
class Socket : public QTcpSocket {
    Q_OBJECT

public:
    Socket();

    // Users tools
    void checkUserStatement(QVector<QString>& userInfo);
    void addUser(QVector<QString>& userInfo);

    bool isUserExists();

private:
    bool isUserExists_ = false;

public slots:
    // Server tools
    void slotReadyRead();

private:
    void sendToServer(int flag, QVector<QString> output);

private:
    quint16 blockSize_ = 0;         // Size of data package

    QTcpSocket* socket_;            // Socket to get/put info from/to server
    QByteArray data_;               // Variable which uses to store relocates data
};
}
