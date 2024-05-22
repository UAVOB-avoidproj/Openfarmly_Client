#ifndef CLIENTJSON_H
#define CLIENTJSON_H

#include <QObject>
#include <iostream>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>


//extern clientJSON *clientjson;
class clientJSON : public QObject
{
    Q_OBJECT
public:
    explicit clientJSON(QObject *parent = nullptr);

private:
    void parseJsonTCP();

    QJsonValue parseJsonDocument();
    QJsonValue parseJsonArray();
    QJsonValue parseJsonKeyValuepair();

private slots:
    void slot_parseJsonDataTCP(QByteArray);

signals:
    void signal_receiveJsonDataTCP(QByteArray);
    void signal_freshJsonDataUI(QString[]);

};

#endif // CLIENTJSON_H
