#ifndef ARMSERVER_H
#define ARMSERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>
#include <QTime>
#include <QDate>

class ARMserver : public QTcpServer
{
    Q_OBJECT
public:
    ARMserver();
    QTcpSocket *socket;

private:
    QVector <QTcpSocket*> Sockets;
    QByteArray Data;
    void SendToClient(QString str);
    quint16 nextBlockSize;

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
};

#endif // ARMSERVER_H
