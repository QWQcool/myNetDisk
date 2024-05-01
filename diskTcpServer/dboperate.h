#ifndef DBOPERATE_H
#define DBOPERATE_H

#include <QObject>
#include <QSqlDatabase> // 连接数据库
#include <QSqlQuery> // 数据库操作
#include <QStringList>

class DBOperate : public QObject
{
    Q_OBJECT
public:
    explicit DBOperate(QObject *parent = nullptr);
    static DBOperate& getInstance();
    DBOperate(DBOperate const&) = delete;
    void operator=(DBOperate const&) = delete;
    void init(); // 初始化函数，数据库连接
    ~DBOperate(); // 析构函数，关闭数据库连接

    // 添加一个公有成员函数，用于调用私有成员函数handleRegist
    bool registerUser(const char *name, const char *pwd) {
        return handleRegist(name, pwd);
    }
    bool LoginUser(const char *name, const char *pwd) {
        return handleLogin(name, pwd);
    }
    bool OfflineUser(const char* name){
        return handleOffline(name);
    }
    QStringList handleOnlineUsers();
    int handleSearchUser(const char *name);
    int handleAddFriend(const char *addedName, const char *sourceName);
    bool handleAddFriendAgree(const char *addedName, const char *sourceName);
    QStringList handleFlushFriendRequest(const char *name);
    bool handleDeleteFriend(const char *deletedName, const char *sourceName);
signals:
private:
    QSqlDatabase m_db; // 连接数据库
    bool handleRegist(const char *name,const char *pwd);
    bool handleLogin(const char *name,const char *pwd);
    bool handleOffline(const char *name);


};

#endif // DBOPERATE_H
