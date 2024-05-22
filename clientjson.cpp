#include "clientjson.h"

clientJSON::clientJSON(QObject *parent) : QObject(parent)
{
    // Bind tcpreceive_sig with parsedata_slot
    connect(this, &clientJSON::signal_receiveJsonDataTCP, this, &clientJSON::slot_parseJsonDataTCP);
}

void clientJSON::slot_parseJsonDataTCP(QByteArray _data){
    QJsonDocument _doc = QJsonDocument::fromJson(_data);
    if(!_doc.isObject()){std::cout<<"erro: doc is no Object";return;}

    QJsonObject _obj = _doc.object();
    QStringList _keys = _obj.keys();
    for(int i=0; i<_keys.size(); ++i)
    {
        QString key = _keys.at(i);
        QJsonValue value = _obj.value(key);
        QString freshUIData[4]{};
        if(value.isString())
        {
            qDebug() << key << "(string):" << value.toString();
            freshUIData[0] = key;
            freshUIData[1] = value.toString();
        }
        if(value.isArray()){
            qDebug() << key << "(array):" << value.toArray();
            freshUIData[0] = key;
            QJsonArray _array = value.toArray();
            for(int j=0; j<_array.size(); j++){
                qDebug() << _array[j];
                QJsonValue _subvalue = _array[j];
                qDebug() << _subvalue.toString();
                freshUIData[j+1] = _subvalue.toString();
            }
        }
        emit signal_freshJsonDataUI(freshUIData);

    }
}
