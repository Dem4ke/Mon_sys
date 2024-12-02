#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MS::Server server;
    if (!server.connectToDatabase()) {
        qCritical() << "database not found";
    }

    return a.exec();
}
