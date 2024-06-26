#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QString>
#include <QHostAddress>
#include "clientjson.h"

extern clientJSON *clientjson;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void slot_freshJsonDataUI(QString[]);

private slots:
    void on_pushButton_Connect_clicked();
    void on_pushButton_Disconnect_clicked();
    void on_pushButton_Send_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket* m_tcp;
};
#endif // WIDGET_H
