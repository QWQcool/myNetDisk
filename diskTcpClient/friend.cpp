#include "friend.h"
#include "tcpclient.h"
#include <QInputDialog>
#include <QMessageBox>

Friend::Friend(QWidget *parent)
    : QWidget{parent}
{
    m_pFriendLW = new QListWidget;
    m_pInputMsgLE = new QLineEdit;
    m_pShowMsgTE = new QTextEdit;
    m_pDelFriendPB = new QPushButton("删除好友");
    m_pFlushFriendPB = new QPushButton("刷新好友");
    m_pShowOnlineUserPB = new QPushButton("显示在线用户");
    m_pSearchUserPB = new QPushButton("查找用户");
    m_pSendMsgPB = new QPushButton("发送");
    m_pPrivateChatPB = new QPushButton("私聊");

    m_pOnline = new Online;

    QVBoxLayout *pLeftRightVBL = new QVBoxLayout; // 左侧右部分好友操作按钮布局
    pLeftRightVBL -> addWidget(m_pPrivateChatPB);
    pLeftRightVBL -> addWidget(m_pDelFriendPB);
    pLeftRightVBL -> addWidget(m_pFlushFriendPB);
    pLeftRightVBL -> addWidget(m_pShowOnlineUserPB);
    pLeftRightVBL -> addWidget(m_pSearchUserPB);
    QHBoxLayout *pRightDownHBL = new QHBoxLayout; // 右侧下方发送消息布局
    pRightDownHBL -> addWidget(m_pInputMsgLE);
    pRightDownHBL -> addWidget(m_pSendMsgPB);

    QVBoxLayout *pRightVBL = new QVBoxLayout; // 右侧聊天布局
    pRightVBL -> addWidget(m_pShowMsgTE);
    pRightVBL -> addLayout(pRightDownHBL);


    QHBoxLayout *pAllHBL = new QHBoxLayout; // 整体水平布局
    pAllHBL -> addWidget(m_pFriendLW);      // 左侧左部分好友列表
    pAllHBL -> addLayout(pLeftRightVBL);    // 左侧右部分好友操作
    pAllHBL -> addLayout(pRightVBL);        // 右侧聊天布局
    // pAllHBL -> addWidget(m_pOnline);  //太丑了
    m_pOnline->hide();

    setLayout(pAllHBL); // 将整体布局pAllHBL设置为页面布局

    // 绑定打开所有在线用户按钮与对应事件
    connect(m_pShowOnlineUserPB, SIGNAL(clicked(bool)),
            this, SLOT(showOrHideOnlineUserW()));
    connect(m_pSearchUserPB, SIGNAL(clicked(bool)),
            this, SLOT(searchUser()));
    connect(m_pFlushFriendPB, SIGNAL(clicked(bool)),
            this, SLOT(flushFriendList()));
    // 绑定删除好友按钮与对应事件
    connect(m_pDelFriendPB, SIGNAL(clicked(bool)),
            this, SLOT(deleteFriend()));
    //绑定私聊按钮
    connect(m_pPrivateChatPB,SIGNAL(clicked(bool)),this,SLOT(privateChat()));
    //绑定群聊按钮
    connect(m_pSendMsgPB,SIGNAL(clicked(bool)),this,SLOT(groupChatSendMsg()));
}

void Friend::setOnlineUsers(PDU *pdu)
{
    if(NULL == pdu)
    {
        return ;
    }
    m_pOnline->setOnlineUsers(pdu);
}

void Friend::updateGroupShowMsgTE(PDU *pdu)
{
    QString strMsg = QString("%1 : %2").arg(pdu->caData).arg((char*)pdu->caMsg);
    m_pShowMsgTE -> append(strMsg);
}

void Friend::showOrHideOnlineUserW()
{
    if(m_pOnline -> isHidden())
    {
        // 显示onlineUserWid页面
        m_pOnline -> show();
        // 发送请求查询数据库获取在线用户
        PDU *pdu = mkPDU(0);
        pdu -> uiMsgType = ENUM_MSG_TYPE_ONLINE_USERS_REQUEST;
        TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu -> uiPDULen);
        free(pdu);
        pdu = NULL;
    }
    else
    {
        m_pOnline -> hide();
    }
}

void Friend::searchUser()
{
    m_strSearchName = QInputDialog::getText(this, "搜索", "用户名："); // 通过输入子页面来获取用户输入返回一个文本类型

    if(!m_strSearchName.isEmpty())
    {
        qDebug() << "查找：" << m_strSearchName;
            PDU *pdu = mkPDU(0);
        pdu -> uiMsgType = ENUM_MSG_TYPE_SEARCH_USER_REQUEST;
        memcpy((char*)pdu -> caData, m_strSearchName.toStdString().c_str(), 32);
        TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu -> uiPDULen);
        free(pdu);
        pdu = NULL;
    }
}

void Friend::flushFriendList()
{
    QString strName = TcpClient::getInstance().getLoginName(); // 获取自己用户名

    PDU* pdu = mkPDU(0);
    pdu -> uiMsgType = ENUM_MSG_TYPE_FLUSH_FRIEND_REQUEST;
    strncpy(pdu -> caData, strName.toStdString().c_str(), strName.size());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu -> uiPDULen);
    free(pdu);
    pdu = NULL;
}

void Friend::updateFriendList(PDU *pdu)
{
    if(NULL == pdu)
    {
        return ;
    }
    uint uiSize = pdu -> uiMsgLen / 36; // 注意是36，32 name + 4 online
    char caName[32] = {'\0'};
    char caOnline[4] = {'\0'};

    m_pFriendLW -> clear(); // 清除好友列表原有数据
    for(uint i = 0; i < uiSize; ++ i)
    {
        memcpy(caName, (char*)(pdu -> caMsg) + i * 36, 32);
        memcpy(caOnline, (char*)(pdu -> caMsg) + 32 + i * 36, 4);
        // qDebug() << "客户端好友" << caName << " " << caOnline;
        m_pFriendLW -> addItem(QString("%1\t%2").arg(caName)
                                 .arg(strcmp(caOnline, "1") == 0?"在线":"离线"));
    }
}

void Friend::deleteFriend()
{
    if(NULL == m_pFriendLW -> currentItem()) // 如果没有选中好友
    {
        return ;
    }
    QString friName = m_pFriendLW -> currentItem() -> text(); // 获得选中的好友用户名
    friName = friName.split("\t")[0];
    QString loginName = TcpClient::getInstance().getLoginName(); // 登录用户用户名

    qDebug() << friName;
    PDU* pdu = mkPDU(0);
    pdu -> uiMsgType = ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST;
    strncpy(pdu -> caData, friName.toStdString().c_str(), 32);
    strncpy(pdu -> caData + 32, loginName.toStdString().c_str(), 32);
    TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu -> uiPDULen);
    free(pdu);
    pdu = NULL;
}

void Friend::privateChat()
{
    if(NULL == m_pFriendLW -> currentItem()) // 如果没有选中好友
    {
        return ;
    }
    QString friName = m_pFriendLW -> currentItem() -> text(); // 获得选中的好友用户名
    friName = friName.split("\t")[0];
    QString loginName = TcpClient::getInstance().getLoginName(); // 登录用户用户名

    PrivateChatWid *priChat = searchPriChatWid(friName.toStdString().c_str());

    if(priChat == NULL) // 没找到该窗口，说明之前没有创建私聊窗口
    {
        priChat = new PrivateChatWid;
        priChat -> setStrChatName(friName);
        priChat -> setStrLoginName(loginName);
        priChat -> setPriChatTitle(friName.toStdString().c_str());
        m_priChatWidList.append(priChat); // 添加入该客户端私聊List
    }
    if(priChat->isHidden()) // 如果窗口被隐藏，则让其显示
    {
        priChat->show();
    }
    if(priChat -> isMinimized()) // 如果窗口被最小化了
    {
        // qDebug() << "窗口被最小化了";
        priChat->showNormal();
    }
}

PrivateChatWid *Friend::searchPriChatWid(const char *pw)
{
    for(int i=0;i<m_priChatWidList.size();i++){
        if(pw==m_priChatWidList[i]->strChatName()){
            return m_priChatWidList[i];
        }
    }
    return NULL;
}

void Friend::insertPriChatWidList(PrivateChatWid *priChat)
{
    m_priChatWidList.append(priChat);
}

void Friend::groupChatSendMsg()
{
    QString strMsg = m_pInputMsgLE -> text();
    if(strMsg.isEmpty())
    {
        QMessageBox::warning(this, "群聊", "发送信息不能为空！");
        return ;
    }
    m_pInputMsgLE->clear(); // 清空输入框
    m_pShowMsgTE->append(QString("%1 : %2").arg(TcpClient::getInstance().getLoginName()).arg(strMsg));

    PDU* pdu = mkPDU(strMsg.size() + 1);
    pdu -> uiMsgType = ENUM_MSG_TYPE_GROUP_CHAT_REQUEST;
    strncpy(pdu -> caData, TcpClient::getInstance().getLoginName().toStdString().c_str(), 32);
    strncpy((char*)(pdu -> caMsg), strMsg.toStdString().c_str(), strMsg.size());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}
