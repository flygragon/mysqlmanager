#include "resetpwd.h"
#include "ui_resetpwd.h"
#include <QMessageBox>

resetPwd::resetPwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resetPwd)
{
    ui->setupUi(this);
}

resetPwd::~resetPwd()
{
    delete ui;
}

QStringList resetPwd::getInput()
{

    QStringList dataList;
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Input Error","User Name Empty!");
        return QStringList();
    }
    if(ui->lineEdit_2->text() !=ui->lineEdit_3->text())
    {
        QMessageBox::warning(this,"Input Error","PassWords Diffrent!");
        return QStringList();
    }
    dataList<<ui->lineEdit->text()
           //<<ui->lineEdit_2->text()
           <<ui->lineEdit_3->text();
    return dataList;
}

