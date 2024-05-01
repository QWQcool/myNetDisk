#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QFile>
#include <QTcpSocket>
#include <QTimer>
#include "protocol.h"  // 服务器需要按照相同协议形式处理数据
#include "dboperate.h" // 操作数据库

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    // MyTcpSocket();
    explicit MyTcpSocket(QObject *parent = nullptr);
    QString getStrName(){
        return m_strName;
    }

    PDU* handleRegistRequest(PDU* pdu);
    PDU* handleLoginRequest(PDU* pdu);
    PDU* handleOnlineUsersRequest();
    // 处理查找用户的请求
    PDU* handleSearchUserRequest(PDU* pdu);
    // 处理添加好友请求
    PDU* handleAddFriendRequest(PDU* pdu);
    // 删除好友请求
    PDU* handleDeleteFriendRequest(PDU* pdu);
    // 私聊发送消息请求
    PDU* handlePrivateChatRequest(PDU* pdu);
    // 群聊请求处理
    void handleGroupChatRequest(PDU* pdu);
    // 创建文件夹请求处理
    PDU* handleCreateDirRequest(PDU* pdu);
    // 刷新文件夹请求处理
    PDU* handleFlushDirRequest(PDU* pdu);
    // 删除文件或文件夹处理
    PDU* handleDelFileOrDirRequest(PDU* pdu);
    // 重命名文件或文件夹请求处理
    PDU* handleRenameFileRequest(PDU* pdu);
    // 进入文件夹请求处理
    PDU* handleEntryDirRequest(PDU* pdu);
    // 返回上一目录请求
    PDU* handlePreDirRequest(PDU* pdu);
    // 上传文件请求处理
    PDU* handleUploadFileRequest(PDU* pdu, TransFile* transFile);
    // 下载文件请求处理
    PDU* handleDownloadFileRequest(PDU* pdu, QFile *fDownloadFile, QTimer *pTimer);
    // 移动文件请求处理
    PDU* handleMoveFileRequest(PDU* pdu);
    // 分享文件请求处理
    PDU* handleShareFileRequest(PDU* pdu, QString strSouName);
    // 分享文件通知响应处理
    PDU* handleShareFileNoteRespond(PDU *pdu);
signals:
    void offline(MyTcpSocket* socket);// 通过信号传送给mytcpserver用户下线通知，然后附带参数socket地址方便删除
public slots:
    void receiveMsg();// 槽函数，按照协议形式处理传输过来的数据
    void handleClientOffline();// 接收客户端下线信号并处理
    void handledownloadFileData(); // 向客户端实际传输要下载的文件数据
private:
    QString m_strName;

    TransFile* m_uploadFile; // 上传文件的信息

    QFile *m_pDownloadFile; // 客户端要下载的文件
    QTimer *m_pTimer; // 计时器
};

#endif // MYTCPSOCKET_H
