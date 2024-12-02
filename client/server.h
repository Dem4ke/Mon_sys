#pragma once

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <vector>

namespace MS {

 class Server {
 public:
     Server();

 private:
     // Work tools
     void openDataToRead(const QString file);
     void openDataToWrite(const QString file);
     void closeData();
     QString firstArgFromBase(QString& line);
     QString secondArgFromBase(QString& line);

 public:
     long int currentDateInSeconds(int currentDate);
     double minValue(QVector<double>& input);
     double maxValue(QVector<double>& input);

 public:
     // Water info
     std::vector<QString> getWaterNames();
     void openProject(QString waterName, QVector<std::pair<QString, QString>>& projectInfo);

 public:
     // Users
     bool isUserExists(QString& login);
     bool isPasswordCorrect(std::vector<QString>& userInfo);
     void addUserData(std::vector<QString>& userInfo);

 private:
     const QString dataPath = "DataBase/";
     const QString usersTable = "users.txt";
     const QString waterTable = "nameOfWaters.txt";
     const QString waterInfo = "Level_of_water_Gulf_of_Finland.txt";

     QFile readWriteInData;
     QTextStream writeStream;
 };
}

