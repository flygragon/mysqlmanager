#include "newaddtion.h"
#include "ui_newaddtion.h"

newAddtion::newAddtion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newAddtion)
{
    ui->setupUi(this);
    connect(this->ui->pushButton,SIGNAL(clicked()),this,SLOT(okClicked()),Qt::UniqueConnection);
    connect(this->ui->pushButton_2,SIGNAL(clicked()),this,SLOT(cancelClicked()),Qt::UniqueConnection);

}

newAddtion::~newAddtion()
{
    delete ui;
}

void newAddtion::setUiLabelText(QString &text)
{
    ui->label->setText(text);
}

void newAddtion::okClicked()
{
    QString tmp =ui->lineEdit->text();
    emit okSignal(tmp);
}
void newAddtion::cancelClicked()
{
    emit cancelSignal();
}
