#ifndef FRIEND_H
#define FRIEND_H

#include <QWidget>
#include <QTextEdit>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "online.h"
#include "protocol.h"
#include "privatechatwid.h"

class Friend : public QWidget
{
    Q_OBJECT
public:
    explicit Friend(QWidget *parent = nullptr);
    void setOnlineUsers(PDU* pdu);
    QString& getStrSearchName(){
        return m_strSearchName;
    }
    void updateGroupShowMsgTE(PDU *pdu);

    QListWidget *getPFriendLW() const{
        return m_pFriendLW;
    }
signals:

public slots:
    void showOrHideOnlineUserW();
    void searchUser();
    void flushFriendList();
    void updateFriendList(PDU *pdu);
    void deleteFriend();
    void privateChat();
    PrivateChatWid* searchPriChatWid(const char* pw);
    void insertPriChatWidList(PrivateChatWid* priChat);
    void groupChatSendMsg();
private:
    QTextEdit *m_pShowMsgTE;
    QListWidget *m_pFriendLW;
    QLineEdit *m_pInputMsgLE;

    QPushButton *m_pDelFriendPB;
    QPushButton *m_pFlushFriendPB;
    QPushButton *m_pShowOnlineUserPB;
    QPushButton *m_pSearchUserPB;
    QPushButton *m_pSendMsgPB;
    QPushButton *m_pPrivateChatPB;

    Online *m_pOnline;

    QString m_strSearchName;

    QList<PrivateChatWid*> m_priChatWidList; // 所有私聊的窗口
};

#endif // FRIEND_H
