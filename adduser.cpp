#include "adduser.h"
#include "ui_adduser.h"
#include <QMessageBox>

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
}

AddUser::~AddUser()
{
    delete ui;
}

QStringList AddUser::getInput()
{
    QStringList dataList;
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Input Error","User Name Empty!");
        return QStringList();
    }
    dataList<<ui->lineEdit->text()
           <<ui->lineEdit_2->text()
          <<ui->lineEdit_3->text();
    if(!ui->lineEdit_4->text().isEmpty())
    {
        if(ui->lineEdit_5->text().isEmpty())
        {
        QMessageBox::warning(this,"Input Error","Previledge DB Name Empty!");
        return QStringList();
        }
        else
        {
        dataList<<ui->lineEdit_4->text()
               <<ui->lineEdit_5->text();
        }
    }
    return dataList;
}




