#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QList>
#include "mytcpsocket.h"

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    MyTcpServer();

    static MyTcpServer &getInstance();
    void incomingConnection(qintptr handle);
    bool forwardMsg(const QString caDesName, PDU *pdu);
    void setStrRootPath(const QString rootPath){
        m_strRootPath=rootPath;
    }
    QString getStrRootPath(){
        return m_strRootPath;
    }

public slots:
    void deleteSocket(MyTcpSocket *mySocket);

private:
    QList<MyTcpSocket*> m_tcpSocketList;
    QString m_strRootPath;

};

#endif // MYTCPSERVER_H
