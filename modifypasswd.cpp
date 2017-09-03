#include "modifypasswd.h"
#include "ui_modifypasswd.h"

modifyPasswd::modifyPasswd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modifyPasswd)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(okClicked()),Qt::UniqueConnection);
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(cancelClicked()),Qt::UniqueConnection);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
}

modifyPasswd::~modifyPasswd()
{
    delete ui;
}

void modifyPasswd::okClicked()
{
    QStringList dataList;
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Input Error","User Name Empty!");
        return;
    }
    if(ui->lineEdit_2->text() !=ui->lineEdit_3->text())
    {
        QMessageBox::warning(this,"Input Error","PassWords Diffrent!");
        return;
    }
    dataList<<ui->lineEdit->text()
           //<<ui->lineEdit_2->text()
           <<ui->lineEdit_3->text();
    emit okSignal(dataList);
    this->close();
}

void modifyPasswd::cancelClicked()
{
    this->close();
}

void modifyPasswd::closeEvent(QCloseEvent *event)
{
    emit closed();
}
