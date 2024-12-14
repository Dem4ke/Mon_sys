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
    QDataStream input(socket);

    input.setVersion(QDataStream::Qt_6_7);
    if (input.status() == QDataStream::Ok) {
        while(true) {
            // Calculate size of the block of data
            if (blockSize_ == 0) {
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

            // Write data from user
            QVector<QString> info;
            int flag;

            input >> flag >> info;

            switch (flag) {
            case 1: {
                addUser(info);
                break;
            }
            case 2: {
                checkUserStatement(info);
                break;
            }
            case 3: {
                getWatersNames();
                break;
            }
            case 4: {
                getWaterInfo(info);
                break;
            }
            }

            blockSize_ = 0;
            break;
        }
    }
    else {
        qDebug() << "DataStream error";
    }
}

void Server::sendToClient(int flag, QVector<QString> output) {
    data_.clear();

    QDataStream out(&data_, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    // Calculate and write a size of the sent data package
    out << quint16(0) << flag << output;
    out.device()->seek(0);
    out << quint16(data_.size() - sizeof(quint16));

    // Send package
    for (auto& s : sockets_) {
        s->write(data_);
    }
}

// Checks is user exists, if not, adds it in database
void Server::addUser(QVector<QString> userInfo) {
    QVector<QString> answerToClient;

    // Check is user with the same login exists
    bool isUserExists = false;
    QSqlQuery query;
    query.exec("SELECT * FROM users");

    while (query.next()) {
        QString dbLogin = query.value("user_login").toString();

        if (userInfo[0] == dbLogin) {
            isUserExists = true;
        }
    }

    if (isUserExists) {
        answerToClient.push_back("denied");
    }
    else {
        answerToClient.push_back("success");

        QString insertInDB = "INSERT INTO users (user_login, user_password, user_email) VALUES ('" +
                             userInfo[0] + "', '" + userInfo[1] + "', '" + userInfo[2] + "');";

        query.exec(insertInDB);
    }

    sendToClient(1, answerToClient);
}


// Checks is user exists and entered password is right
void Server::checkUserStatement(QVector<QString> userInfo) {
    QVector<QString> answerToClient;

    // Check is user with the same login and pasword exists
    bool isUserExists = false;
    QSqlQuery query;
    query.exec("SELECT * FROM users");

    while (query.next()) {
        QString dbLogin = query.value("user_login").toString();
        QString dbPassword = query.value("user_password").toString();

        if (userInfo[0] == dbLogin && userInfo[1] == dbPassword) {
            isUserExists = true;
        }
    }

    if (isUserExists) {
        answerToClient.push_back("success");
    }
    else {
        answerToClient.push_back("denied");
    }

    sendToClient(2, answerToClient);
}

void Server::getWatersNames() {
    QVector<QString> answerToClient;

    QSqlQuery query;
    query.exec("SELECT * FROM waters");

    while (query.next()) {
        QString waterName = query.value("water_name").toString();
        answerToClient.push_back(waterName);
    }

    sendToClient(3, answerToClient);
}

void Server::getWaterInfo(QVector<QString> waterName) {
    QVector<QString> answerToClient;
    int category = 0;

    QSqlQuery query;
    query.exec("SELECT * FROM waters");

    // Get info about category of water
    while (query.next()) {
        QString dbWaterName = query.value("water_name").toString();

        if (waterName[0] == dbWaterName) {
            category = query.value("category").toInt();
            break;
        }
    }

    // Get info about water's limits
    query.exec("SELECT * FROM categories");

    while (query.next()) {
        int categoryId = query.value("category_id").toInt();

        if (categoryId == category) {
            QString waterLevelLimit = query.value("water_level_limit").toString();
            answerToClient.push_back(waterLevelLimit);
            break;
        }
    }

    // Get info about water level and date of measurements
    query.exec("SELECT * FROM public.\"" + waterName[0] + "\"");

    while (query.next()) {
        QString date = query.value("date").toString();
        QString waterLevel = query.value("water_level").toString();

        answerToClient.push_back(date);
        answerToClient.push_back(waterLevel);
    }

    sendToClient(4, answerToClient);
}
}
