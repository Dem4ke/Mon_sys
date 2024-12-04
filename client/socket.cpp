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
void Socket::checkUserStatement(QVector<QString>& userInfo) {
    sendToServer(2, userInfo);
}

// Add new user in database
void Socket::addUser(QVector<QString>& userInfo) {
    sendToServer(1, userInfo);
}

bool Socket::isUserExists() const {
    return isUserExists_;
}

//--------------------------------------------------------------------------------------------------------------------------
// WATERS TOOLS

// Send request to get waters names from database
void Socket::setWatersNamesRequest() {
    QVector<QString> info;
    sendToServer(3, info);
}

// Get waters names
QVector<QString> Socket::getWatersNames() const {
    return watersNames_;
}

//--------------------------------------------------------------------------------------------------------------------------
// SERVER TOOLS

// Handler of a client's messages
void Socket::slotReadyRead() {
    isUserExists_ = false;

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
            QVector<QString> info;
            int flag;

            input >> flag >> info;

            switch (flag) {
            case 1: {
                if (info[0] == "denied") {
                    isUserExists_ = true;
                }
                else if (info[0] == "success") {
                    isUserExists_ = false;
                }

                break;
            }
            case 2: {
                if (info[0] == "denied") {
                    isUserExists_ = false;
                }
                else if (info[0] == "success") {
                    isUserExists_ = true;
                }

                break;
            }
            case 3: {
                watersNames_ = info;
                break;
            }
            }

            blockSize_ = 0;
            break;
        }
    }
}

void Socket::sendToServer(int flag, QVector<QString> output) {
    data_.clear();

    QDataStream out(&data_, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    // Calculate and write a size of the sent data package
    out << quint16(0) << flag << output;
    out.device()->seek(0);
    out << quint16(data_.size() - sizeof(quint16));

    // Send package
    socket_->write(data_);
}
}

