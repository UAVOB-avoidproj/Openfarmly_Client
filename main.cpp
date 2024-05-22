#include "widget.h"

#include <QTcpSocket>
#include <QApplication>
#include "clientjson.h"

clientJSON *clientjson = nullptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    clientjson = new clientJSON();
    // Bind freshUI_sig with freshUI_slot
    QObject::connect(clientjson, &clientJSON::signal_freshJsonDataUI, &w, &Widget::slot_freshJsonDataUI);

    return a.exec();
}
