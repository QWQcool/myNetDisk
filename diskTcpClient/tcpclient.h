#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QFile>
#include <QTcpSocket>
#include "protocol.h"
#include "operatewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class TcpClient;
}
QT_END_NAMESPACE

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    TcpClient(QWidget *parent = nullptr);
    ~TcpClient();
    void loadConfig();
public slots:
    void showConnect();
    void receiveMsg();

    static TcpClient &getInstance();
    QTcpSocket &getTcpSocket();
    QString getLoginName(){
        return m_strLoginName;
    }
    QString getStrCurPath(){
        return m_strCurPath;
    }
    QString getStrRootPath(){
        return m_strRootPath;
    }

private slots:
    // void on_send_pb_clicked();

    void on_login_pb_clicked();

    void on_regist_pb_clicked();

    void on_cancel_pb_clicked();

private:
    Ui::TcpClient *ui;
    QString m_strIP;
    quint16 m_usPort;
    //连接服务器和服务器数据交互
    QTcpSocket m_tcpSocket;
    QString m_strLoginName;
    //文件路径
    QString m_strCurPath;
    //文件根路径
    QString m_strRootPath;
};
#endif // TCPCLIENT_H
