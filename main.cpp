#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTcpServer server;
    QList<QTcpSocket*> sockets;
    server.listen(QHostAddress::Any, 7890);

    // wait for first connection
    if(server.waitForNewConnection(-1) && server.hasPendingConnections()  ) {
        QTcpSocket * nwsock = server.nextPendingConnection();
        sockets.append(nwsock);
        while(nwsock->isValid()) {
            if(nwsock->waitForReadyRead()) {
                qDebug() << "Data:" << QString(nwsock->readAll());
            }
        }
    }
    qDebug() << "finito";
    return 0;
}
