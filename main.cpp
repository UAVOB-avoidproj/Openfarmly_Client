#include "widget.h"

#include <QTcpSocket>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();




    return a.exec();
}
