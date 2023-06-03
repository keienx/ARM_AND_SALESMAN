#include "armserver.h"
ARMserver::ARMserver()
{
    if(this->listen(QHostAddress::Any, 2323)){
        qDebug() << "Сервер запущен";
    }
    else{
        qDebug() << "Ошибка в запуске севрера";
    }
    nextBlockSize = 0;
}
void ARMserver::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &ARMserver::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &ARMserver::deleteLater);

    Sockets.push_back(socket);
    qDebug() << "Client connected" << socketDescriptor;
}

void ARMserver::slotReadyRead(){
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    if (in.status() == QDataStream::Ok){
        /*QString str;
        in >> str;
        qDebug() << str;
        SendToClient(str);*/
        for (;;){
            if (nextBlockSize == 0){
                if (socket->bytesAvailable() < 2){
                    break;
                }
                in >> nextBlockSize;
            }
            if (socket->bytesAvailable() < nextBlockSize){
                break;
            }
            QString str;
            QTime time;
            in >> time >> str;
            nextBlockSize = 0;
            SendToClient(str);
            qDebug() << str;
            break;
        }
    }
    else{
        qDebug() << "Ошибка в потоке";
    }
}

void ARMserver::SendToClient(QString str){
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << quint16(0) << QTime::currentTime() <<  str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    //socket->write(Data);
    for (int i = 0; i < Sockets.size(); i++){
        Sockets[i]->write(Data);
    }
}
