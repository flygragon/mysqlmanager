#include "newuser.h"
#include "ui_newuser.h"

newUser::newUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newUser)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(okClicked()),Qt::UniqueConnection);
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(cancelClicked()),Qt::UniqueConnection);
}

newUser::~newUser()
{
    delete ui;
}


void newUser::okClicked()
{
    QStringList dataList;
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Input Error","User Name Empty!");
        return;
    }
    dataList<<ui->lineEdit->text()
           <<ui->lineEdit_2->text()
          <<ui->lineEdit_3->text();
    if(!ui->lineEdit_4->text().isEmpty())
    {
        if(ui->lineEdit_5->text().isEmpty())
        {
        QMessageBox::warning(this,"Input Error","Previledge DB Name Empty!");
        return;
        }
        else
        {
        dataList<<ui->lineEdit_4->text()
               <<ui->lineEdit_5->text();
        }
    }
    emit okSignal(dataList);
    this->close();
}

void newUser::cancelClicked()
{
    this->close();
}

void newUser::closeEvent(QCloseEvent *event)
{
    emit closed();
}


