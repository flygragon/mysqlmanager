#include "createconnection.h"
#include "ui_createconnection.h"
#include <QDebug>

createConnection::createConnection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::createConnection)
{
    ui->setupUi(this);
    ui->lineEdit_5->setEchoMode(QLineEdit::Password);
    connect(this->ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()),Qt::UniqueConnection);
    connect(this->ui->pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()),Qt::UniqueConnection);
    qDebug()<<"New Connection Created";
}

createConnection::~createConnection()
{
    delete ui;
}

/*void createConnection::inputComplete1()
{
    qDebug()<<"Input Complete";
}*/

void createConnection::on_pushButton_clicked()
{
    conInfo.clear();
    conInfo.push_back(ui->lineEdit->text());
    conInfo.push_back(ui->lineEdit_2->text());
    conInfo.push_back(ui->lineEdit_3->text());
    conInfo.push_back(ui->lineEdit_4->text());
    conInfo.push_back(ui->lineEdit_5->text());
    emit inputComplete();
}

std::vector<QString>& createConnection::getConInfo()
{
    qDebug()<<"Got Input Info";
    return this->conInfo;
}

void createConnection::on_pushButton_2_clicked()
{
    emit cancel();
    this->close();
}
