#include "tcpserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DBOperate::getInstance().init();
    TcpServer w;
    w.show();
    return a.exec();
}
