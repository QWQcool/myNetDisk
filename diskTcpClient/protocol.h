#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdlib.h>
#include <unistd.h> // Unix库函数，包含了read等系统服务函数
#include <string.h>
#include <QFile>

typedef unsigned int uint;

#define REGIST_OK "regist ok"
#define REGIST_FAILED "regist failed"
#define LOGIN_OK "login ok"
#define LOGIN_FAILED "login failed"
#define SEARCH_USER_OK "online"
#define SEARCH_USER_OFFLINE "unonline"
#define SEARCH_USER_EMPTY "is empty"

#define ADD_FRIEND_OFFLINE "user offline"
#define ADD_FRIEND_OK "send add friend message"
#define ADD_FRIEND_EMPTY "not user"
#define ADD_FRIEND_EXIST "exist friend"
#define UNKNOWN_ERROR "unknown error"

#define DEL_FRIEND_OK "delete friend successful"
#define DEL_FRIEND_FAILED "delete friend failed"

#define PRIVATE_CHAT_OFFLINE "private offline"

#define CREATE_DIR_EXIST "File exist"
#define CREATE_DIR_OK "File ok"
#define PATH_NOT_EXIST "File path not exist"

#define FLUSH_DIR_OK "flush dir ok"                      // 刷新文件夹
#define FLUSH_DIR_FAILED "flush dir failed"

#define DELETE_FILE_OK "delete file ok"                  // 删除文件夹
#define DELETE_FILE_FAILED "delete file failed"

#define RENAME_FILE_OK "rename file ok"                  // 重命名文件
#define RENAME_FILE_FAILED "rename file failed"

#define ENTRY_DIR_OK "entry dir ok"                      // 进入目录
#define ENTRY_DIR_FAILED "entry dir failed"

#define PRE_DIR_OK "return pre dir ok"                   // 上一目录
#define PRE_DIR_FAILED "return pre dir failed"

#define UPLOAD_FILE_OK "upload file ok"                  // 上传文件
#define UPLOAD_FILE_FAILED "upload file failed"
#define UPLOAD_FILE_START "start upload file data"

#define DOWNLOAD_FILE_OK "download file ok"              // 下载文件
#define DOWNLOAD_FILE_FAILED "download file failed"
#define DOWNLOAD_FILE_START "start download file data"

#define MOVE_FILE_OK "move file ok"                      // 移动文件
#define MOVE_FILE_FAILED "move file failed"

#define SHARE_FILE_OK "share file ok"                      // 移动文件
#define SHARE_FILE_FAILED "share file failed"

#define UNKNOWN_ERROR "unknown error"                    // 通用未知错误

enum ENUM_MSG_TYPE{
    ENUM_MSG_TYPE_MIN=0,
    ENUM_MSG_TYPE_REGIST_REQUEST, //注册请求
    ENUM_MSG_TYPE_REGIST_RESPOND, //注册回复
    ENUM_MSG_TYPE_LOGIN_REQUEST,  //登录请求
    ENUM_MSG_TYPE_LOGIN_RESPOND, //登陆回复
    ENUM_MSG_TYPE_ONLINE_USERS_REQUEST, //在线用户请求
    ENUM_MSG_TYPE_ONLINE_USERS_RESPOND, //在线用户回复
    ENUM_MSG_TYPE_SEARCH_USER_REQUEST, //搜索用户请求
    ENUM_MSG_TYPE_SEARCH_USER_RESPOND, //搜索用户回复
    ENUM_MSG_TYPE_ADD_FRIEND_REQUEST, //添加好友请求
    ENUM_MSG_TYPE_ADD_FRIEND_RESPOND,  //添加好友回复
    ENUM_MSG_TYPE_ADD_FRIEND_AGREE,  //同意添加好友
    ENUM_MSG_TYPE_ADD_FRIEND_REJECT, //拒绝添加好友
    ENUM_MSG_TYPE_FLUSH_FRIEND_REQUEST,//刷新好友请求
    ENUM_MSG_TYPE_FLUSH_FRIEND_RESPOND,//刷新好友回复
    ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST,//删除好友请求
    ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND,//删除好友回复
    ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST,//私聊用户请求
    ENUM_MSG_TYPE_PRIVATE_CHAT_RESPOND,//私聊用户回复
    ENUM_MSG_TYPE_GROUP_CHAT_REQUEST, //群聊用户请求
    ENUM_MSG_TYPE_GROUP_CHAT_RESPOND, //群聊用户回复
    ENUM_MSG_TYPE_CREATE_DIR_REQUEST, //创造文件夹请求
    ENUM_MSG_TYPE_CREATE_DIR_RESPOND, //创造文件夹回复
    ENUM_MSG_TYPE_FLUSH_DIR_REQUEST, //刷新文件夹请求
    ENUM_MSG_TYPE_FLUSH_DIR_RESPOND, //刷新文件夹回复
    ENUM_MSG_TYPE_DELETE_FILE_REQUEST, // 删除文件夹请求
    ENUM_MSG_TYPE_DELETE_FILE_RESPOND, // 删除文件夹回复
    ENUM_MSG_TYPE_RENAME_FILE_REQUEST, // 重命名文件夹请求
    ENUM_MSG_TYPE_RENAME_FILE_RESPOND, // 重命名文件夹回复
    ENUM_MSG_TYPE_ENTRY_DIR_REQUEST, //进入文件夹请求
    ENUM_MSG_TYPE_ENTRY_DIR_RESPOND, //进入文件夹回复

    ENUM_MSG_TYPE_PRE_DIR_REQUEST, // 上一文件夹请求
    ENUM_MSG_TYPE_PRE_DIR_RESPOND, // 上一文件夹回复

    ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST, // 上传文件请求
    ENUM_MSG_TYPE_UPLOAD_FILE_RESPOND, // 上传文件回复

    ENUM_MSG_TYPE_DOWNLOAD_FILE_REQUEST, // 下载文件请求
    ENUM_MSG_TYPE_DOWNLOAD_FILE_RESPOND, // 下载文件响应

    ENUM_MSG_TYPE_MOVE_FILE_REQUEST, // 移动文件请求
    ENUM_MSG_TYPE_MOVE_FILE_RESPOND, // 移动文件响应

    ENUM_MSG_TYPE_SHARE_FILE_REQUEST, // 移动文件请求
    ENUM_MSG_TYPE_SHARE_FILE_RESPOND, // 移动文件响应
    ENUM_MSG_TYPE_SHARE_FILE_NOTE, // 移动文件提示
    ENUM_MSG_TYPE_SHARE_FILE_NOTE_RESPOND, // 移动文件提示响应
    ENUM_MSG_TYPE_MAX=0x00ffffff //uint最大值

};
// 设计协议数据单元格式
struct PDU{
    uint uiPDULen;  //总的协议数据单元大小
    uint uiMsgType; //消息类型
    char caData[64];
    uint uiMsgLen;  //实际消息长度
    int caMsg[];  //实际消息
};

// 文件信息结构体
struct FileInfo
{
    char caName[32];     // 文件名字
    bool bIsDir;         // 文件类型，是否为文件夹
    long long uiSize;         // 文件大小
    char caTime[128];    // 修改时间
};

// 传输文件信息
struct TransFile
{
    QFile file; // 上传的文件
    qint64 iTotalSize; // 文件总大小
    qint64 iReceivedSize; // 已接收大小
    bool bTransform; // 是否正在传输文件
};

PDU *mkPDU(uint uiMsgLen);

#endif // PROTOCOL_H
