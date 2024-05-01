#ifndef OPERATEWIDGET_H
#define OPERATEWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include "filesystem.h"
#include "friend.h"

class OperateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OperateWidget(QWidget *parent = nullptr);
    static OperateWidget &getInstance();
    Friend *getPFriend(){
        return m_pFriend;
    }
    FileSystem* getPFileSystem(){
        return m_pFileSystem;
    }
    // void insertPriChatWidList(priChatW);
signals:

public slots:

private:
    QListWidget *m_pListW;
    Friend *m_pFriend;          // 好友页面
    FileSystem *m_pFileSystem;  // 文件页面
    QStackedWidget *m_pSW;      // 容器，每次显示一个页面（好友or文件）
};

#endif // OPERATEWIDGET_H
