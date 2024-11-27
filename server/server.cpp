#include "server.h"

Server::Server() {
    // Checks server state, if it works said start
    if (this->listen(QHostAddress::Any, 2323)) {
        qDebug() << "start";
    }
    else {
        qDebug() << "error";
    }
}

// Handler of a new connections
void Server::incomingConnection(qintptr socketDescriptor) {
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(
    connect(socket, this, &Server::slotReadyRead);

    sockets_.push_back(socket);

    qDebug() << "client connected: " << socketDescriptor;
}

// Handler of a client's disconnection
void Server::clienDisconnected() {
    // The socket which sent a request
    socket = (QTcpSocket*)sender();

    // Delete socket of a client which left
    sockets_.erase(std::remove(sockets_.begin(), sockets_.end(), socket), sockets_.end());
    socket->deleteLater();
}

// Handler of a client's messages
void Server::slotReadyRead() {
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);

    in.setVersion(QDataStream::Qt_6_7);

    if (in.status() == QDataStream::Ok) {
        QString input;
        in >> input;

        qDebug() << "read " << input;
    }
    else {
        qDebug() << "DataStream error";
    }
}

void Server::sentToClient(QString output) {
    data_.clear();

    QDataStream out(&data_, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << output;
    socket->write(data_);
}

