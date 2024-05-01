#include "operatewidget.h"

OperateWidget::OperateWidget(QWidget *parent)
    : QWidget{parent}
{
    m_pListW = new QListWidget(this);
    m_pListW->addItem("好友");
    m_pListW->addItem("文件");

    m_pFriend = new Friend;
    m_pFileSystem = new FileSystem;

    m_pSW = new QStackedWidget;
    m_pSW -> addWidget(m_pFriend);     // 如果没有设置，默认显示第一个页面
    m_pSW -> addWidget(m_pFileSystem);

    QHBoxLayout *pMainHBL = new QHBoxLayout;
    pMainHBL -> addWidget(m_pListW);
    pMainHBL -> addWidget(m_pSW);

    setLayout(pMainHBL);

    // 将m_pListWidget的行号变化信号与m_pSW的设置当前页面槽函数关联
    connect(m_pListW, SIGNAL(currentRowChanged(int)), // 函数参数为改变后的行号
            m_pSW, SLOT(setCurrentIndex(int))); // 函数参数为设置的页面下标
}

OperateWidget &OperateWidget::getInstance()
{
    static OperateWidget instance;
    return instance;
}
