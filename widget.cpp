#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->pushButton_Disconnect->setDisabled(true); // 初始时 ，断开连接按钮不可用

    ui->lineEdit_Port->setText("8081"); // 默认端口
    ui->lineEdit_IP->setText("127.0.0.1"); // 默认ip
    ui->textEdit_SendMessage->setPlaceholderText("请输入指令");

    // 创建通信的套接字
    m_tcp = new QTcpSocket(this);

    // 接受到服务端消息
    connect(m_tcp,&QTcpSocket::readyRead,this,[=](){
        QByteArray data = m_tcp->readAll();
         ui->textEdit_Historymessage->append("服务器 ： " + data);
         emit clientjson->signal_receiveJsonDataTCP(data);
        // readData();
    });

    // 服务器端断开连接
    connect(m_tcp,&QTcpSocket::disconnected ,this,[=](){
        m_tcp->close();
        //m_tcp->deleteLater(); // 封装 delete
        ui->textEdit_Historymessage->append("已经和服务器断开连接....");

        ui->pushButton_Connect->setDisabled(false);// 设置连接按钮不可用
        ui->pushButton_Disconnect->setDisabled(true);
    });

    // 检测连接状态
    connect(m_tcp,&QTcpSocket::connected ,this,[this](){
        ui->textEdit_Historymessage->append("连接服务器成功...");

        ui->pushButton_Connect->setDisabled(true);
        ui->pushButton_Disconnect->setDisabled(false);
    });

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_Connect_clicked()
{
    QString ip = ui->lineEdit_IP->text();
    unsigned short port = ui->lineEdit_Port->text().toUShort();
    m_tcp->connectToHost(QHostAddress(ip) , port);
}

void Widget::on_pushButton_Disconnect_clicked()
{
    m_tcp->close();
    ui->pushButton_Disconnect->setDisabled(true);
    ui->pushButton_Connect->setDisabled(false);
}

void Widget::on_pushButton_Send_clicked()
{
    QString msg = ui->textEdit_SendMessage->toPlainText();
    m_tcp->write(msg.toUtf8()+"\n"); // 输入客户端
    ui->textEdit_Historymessage->append("客户端 ： " + msg);
    ui->textEdit_SendMessage->clear();
}

void Widget::slot_freshJsonDataUI(QString freshUIData[]){
    if(freshUIData[0] == "FlightMode"){
        ui->FlightMode_value->setText(freshUIData[1]);
    }else if(freshUIData[0] == "Angular_Velocity_body"){
        ui->label_angularvelocity_x->setText(freshUIData[1]);
        ui->label_angularvelocity_y->setText(freshUIData[2]);
        ui->label_angularvelocity_z->setText(freshUIData[3]);
    }else if(freshUIData[0] == "EulerAngle"){
        ui->label_attitude_x->setText(freshUIData[1]);
        ui->label_attitude_y->setText(freshUIData[2]);
        ui->label_attitude_z->setText(freshUIData[3]);
    }else if(freshUIData[0] == "Position"){
        ui->latitude_value->setText(freshUIData[1]);
        ui->longitude_value->setText(freshUIData[2]);
    }else if(freshUIData[0] == "Position_body"){
        ui->label_position_x->setText(freshUIData[1]);
        ui->label_position_x->setText(freshUIData[2]);
        ui->label_position_x->setText(freshUIData[3]);
    }else if(freshUIData[0] == "Velocity_body"){
        ui->label_velocity_x->setText(freshUIData[1]);
        ui->label_velocity_y->setText(freshUIData[2]);
        ui->label_velocity_z->setText(freshUIData[3]);
    }else{
        std::cout<<"freshUI ERRO!";
    }
}
