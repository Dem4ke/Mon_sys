#include "server.h"

namespace MS{
Server::Server() {
    // Checks server state, if it works said start
    if (this->listen(QHostAddress::Any, 2323)) {
        qDebug() << "start";
    }
    else {
        qDebug() << "error";
    }
}

// Create connection with database
bool Server::connectToDatabase() {
    // Database which contains all information about users and waters
    QSqlDatabase watersBD = QSqlDatabase::addDatabase("QPSQL");
    watersBD.setDatabaseName("waters_info");
    watersBD.setUserName("postgres");
    watersBD.setPassword("1337");

    if (!watersBD.open()) {
        QSqlError error = watersBD.lastError();
        qCritical() << "waters database error" << error.text();
        return false;
    }

    watersBD.tables(QSql::AllTables);
    qCritical() << "Database opened, tables:" << watersBD.tables(QSql::Tables);
    return true;
}

// Handler of a new connections
void Server::incomingConnection(qintptr socketDescriptor) {
    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    //connect(socket, &QTcpSocket::readyRead, this, &MS::Server::slotReadyRead);

    sockets_.push_back(socket);

    qDebug() << "client connected: " << socketDescriptor;
    sendToClient("Connection success");
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

    // Проверить как определяется сокет, которому надо будет доставить сообщение (скорее всего по дискриптору)
    qDebug() << socket;
    //
    QDataStream input(socket);

    input.setVersion(QDataStream::Qt_6_7);
    if (input.status() == QDataStream::Ok) {
        while(true) {
            // Calculate size of the block of data
            if (blockSize_ == 0) {
                qDebug() << blockSize_;
                if (socket->bytesAvailable() < 2) {
                    break;
                }

                // Write the block size
                input >> blockSize_;
            }

            // If the block size is bigger than data from client, we should wait to other data
            if (socket->bytesAvailable() < blockSize_) {
                qDebug() << "data not full, break";
                break;
            }

            // Write data to server
            QString str;
            input >> str;

            QSqlQuery query;
            query.exec(str);
            // Работа с базой данных и проверка необходимой информации
            // Здесь будет проходить проверка по флагу и будет вызываться функция с запросом
            /*switch (index) {
                case 0: {
                break;
                }
            }*/

            blockSize_ = 0;
            break;
        }
    }
    else {
        qDebug() << "DataStream error";
    }
}

void Server::sendToClient(QString output) {
    data_.clear();

    QDataStream out(&data_, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    // Calculate and write a size of the sent data package
    out << quint16(0) << output;
    out.device()->seek(0);
    out << quint16(data_.size() - sizeof(quint16));

    // Send package
    for (auto& s : sockets_) {
        s->write(data_);
    }
}
}
