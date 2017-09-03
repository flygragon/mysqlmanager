#include "newconnection.h"
#include "ui_newconnection.h"

newConnection::newConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newConnection)
{
    ui->setupUi(this);
}

newConnection::~newConnection()
{
    delete ui;
}

std::vector<QString>& newConnection::getConInfo()
{
    conInfo.clear();
    conInfo.push_back(ui->lineEdit->text());
    conInfo.push_back(ui->lineEdit_2->text());
    conInfo.push_back(ui->lineEdit_3->text());
    conInfo.push_back(ui->lineEdit_4->text());
    conInfo.push_back(ui->lineEdit_5->text());
    return this->conInfo;
}
