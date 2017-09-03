#include "setbackuppath.h"
#include "ui_setbackuppath.h"
#include <QFileDialog>



setBackupPath::setBackupPath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setBackupPath)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(getFileDialogPath()),Qt::UniqueConnection);
}

setBackupPath::~setBackupPath()
{
    delete ui;
}

void setBackupPath::getFileDialogPath()
{

}


