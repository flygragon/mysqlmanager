#include "additionnew.h"
#include "ui_additionnew.h"

AdditionNew::AdditionNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdditionNew)
{
    ui->setupUi(this);
}

AdditionNew::~AdditionNew()
{
    delete ui;
}

void AdditionNew::setUiLabelText(QString &text)
{
    ui->label->setText(text);
}

QString AdditionNew::getInput()
{
    return ui->lineEdit->text();
}


