#include "server.h"

namespace MS {

 Server::Server() {}

 // WORK TOOLS

 // Open data base to read
 void Server::openDataToRead(const QString file) {
     readWriteInData.setFileName(dataPath + file);
     readWriteInData.open(QIODevice::ReadOnly | QIODevice::Text);
 }

 // Open data base to write
 void Server::openDataToWrite(const QString file) {
     readWriteInData.setFileName(dataPath + file);
     readWriteInData.open(QIODevice::Append | QIODevice::Text);
 }

 // Close data base
 void Server::closeData() {
     readWriteInData.close();
 }

 // Take first arg from base
 QString Server::firstArgFromBase(QString& line) {
     QString first;

     for (auto& i : line) {
         if (i == ' ') {
             break;
         }
         first.push_back(i);
     }

     return first;
 }

 // Take second arg from base
 QString Server::secondArgFromBase(QString& line) {
     QString second;
     bool flag = false;

     for (auto& i : line) {
         if (flag == true && (i == ' ' || i == '\n')) {
             break;
         }
         if (i == ' ') {
             flag = true;
         } else if (flag == true) {
             second.push_back(i);
         }
     }

     return second;
 }

 // Convert current date to seconds from 01.01.1970
 long int Server::currentDateInSeconds(int currentDate) {
     long int seconds = 0;


     return seconds;
 }

 // Search minimum and maximum value
 double Server::minValue(QVector<double>& input) {
     double min = input[0];

     for (auto& i : input) {
         if (min > i) {
             min = i;
         }
     }
     return min;
 }

 double Server::maxValue(QVector<double> &input) {
     double max = input[0];

     for (auto& i : input) {
         if (max < i) {
             max = i;
         }
     }
     return max;
 }

 // WATER INFO
 std::vector<QString> Server::getWaterNames() {
     std::vector<QString> waterNames;

     openDataToRead(waterTable);
     QTextStream readStream(&readWriteInData);

     while (!readWriteInData.atEnd()) {
         QString line = readWriteInData.readLine();
         waterNames.push_back(line);
     }

     closeData();
     return waterNames;
 }

 // Open the project which interested by user
 void Server::openProject(QString waterName, QVector<std::pair<QString, QString>>& projectInfo) {
     // сделать switch зависящий от разных графиков
     // передавать битовую маску или индекс на определенный график
  //   switch(plotIndex) {

    // }
   //  if (waterName == "Gulf of Finland") {
         openDataToRead(waterInfo);
         QTextStream readStream(&readWriteInData);

         while (!readWriteInData.atEnd()) {
             QString line = readWriteInData.readLine();
             QString first = firstArgFromBase(line);
             QString second = secondArgFromBase(line);
             projectInfo.push_back({ first, second });
         }
 //    }


     closeData();
 }

 // USERS

 // Search user in data base
 bool Server::isUserExists(QString& login) {
     openDataToRead(usersTable);
     QTextStream readStream(&readWriteInData);

     while (!readWriteInData.atEnd()) {
         QString line = readWriteInData.readLine();
         QString loginFromData = firstArgFromBase(line);

         if (login == loginFromData) {
             return true;
         }
     }

     closeData();
     return false;
 }

 // Check of password correction
 bool Server::isPasswordCorrect(std::vector<QString> &userInfo) {
     openDataToRead(usersTable);
     QTextStream readStream(&readWriteInData);
     QString searchedLogin = userInfo[0];
     QString searchedPassword = userInfo[1];

     while (!readWriteInData.atEnd()) {
         QString line = readWriteInData.readLine();
         QString loginFromData = firstArgFromBase(line);
         QString passwordFromData = secondArgFromBase(line);

         if (searchedLogin == loginFromData
                 && searchedPassword == passwordFromData) {
             return true;
         }
     }

     closeData();
     return false;
 }

 // Add a new user in data base
 void Server::addUserData(std::vector<QString>& userInfo) {
     openDataToWrite(usersTable);
     QTextStream writeStream(&readWriteInData);
     for (int i = 0, end = userInfo.size(); i < end; ++i) {
         writeStream << userInfo[i] << " ";
     }
     writeStream << '\n';
     closeData();
 }

}
