#include "socket.h"

namespace MS {
Socket::Socket() : QTcpSocket() {
    // Connect application to server
    socket_ = new QTcpSocket(this);
    connect(socket_, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(socket_, &QTcpSocket::disconnected, socket_, &QTcpSocket::deleteLater);
    socket_->connectToHost("127.0.0.1", 2323);
}

//--------------------------------------------------------------------------------------------------------------------------
// USERS TOOLS

// Check is user exists and his password was writed right
void Socket::checkUserStatement(std::vector<QString>& userInfo) {


}

// Add new user in database
bool Socket::addUser(std::vector<QString>& userInfo) {
    QString insertInDB = "INSERT INTO users (user_login, user_password, user_email) VALUES ('" +
                         userInfo[0] + "', '" + userInfo[1] + "', '" + userInfo[2] + "');";

    sendToServer(insertInDB);

    return false;
}

bool Socket::isUserExists() {
    return isUserExists_;
}

//--------------------------------------------------------------------------------------------------------------------------
// SERVER TOOLS

// Handler of a client's messages
void Socket::slotReadyRead() {
    QDataStream input(socket_);
    input.setVersion(QDataStream::Qt_6_7);

    if (input.status() == QDataStream::Ok) {
        while(true) {
            // Calculate size of the block of data
            if (blockSize_ == 0) {
                if (socket_->bytesAvailable() < 2) {
                    break;
                }

                // Write the block size
                input >> blockSize_;
            }

            // If the block size is bigger than data from server, we should wait to other data
            if (socket_->bytesAvailable() < blockSize_) {
                break;
            }

            // Write data from server
            input_.clear();
            input >> input_;

            blockSize_ = 0;
        }
    }

    // Куда-то отправить информацию из полученной строки
}

void Socket::sendToServer(QString output) {
    data_.clear();

    QDataStream out(&data_, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    // Calculate and write a size of the sent data package
    out << quint16(0) << output;
    out.device()->seek(0);
    out << quint16(data_.size() - sizeof(quint16));

    // Send package
    socket_->write(data_);
}

void Socket::sendToServer(QVector<QString> output) {
    data_.clear();

    QDataStream out(&data_, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    // Calculate and write a size of the sent data package
    out << quint16(0) << output;
    out.device()->seek(0);
    out << quint16(data_.size() - sizeof(quint16));

    // Send package
    socket_->write(data_);
}
}

