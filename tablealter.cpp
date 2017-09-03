#include "tablealter.h"
#include "ui_tablealter.h"

tableAlter::tableAlter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tableAlter)
{
    ui->setupUi(this);
    connect(ui->comboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(OpChangedSlot(QString)),Qt::AutoConnection);
    connect(ui->comboBox_2,SIGNAL(currentTextChanged(QString)),this,SLOT(TypeChangedSlot(QString)),Qt::AutoConnection);
    OpChangedSlot("add");
}

tableAlter::~tableAlter()
{
    delete ui;
}

void tableAlter::OpChangedSlot(QString currentOp)
{
    if(currentOp.contains("add",Qt::CaseInsensitive))
    {
        ui->comboBox_2->clear();
        ui->comboBox_2->addItem("column");
        ui->comboBox_2->addItem("index");
        ui->comboBox_2->addItem("constraint");
        ui->comboBox_2->addItem("unique");
        ui->comboBox_2->addItem("primary key");
        ui->comboBox_2->setVisible(true);
        ui->label_2->setVisible(true);

    }
    else if(currentOp.contains("drop",Qt::CaseInsensitive))
    {
        ui->comboBox_2->clear();
        ui->comboBox_2->addItem("column");
        ui->comboBox_2->addItem("index");
        ui->comboBox_2->addItem("primary key");
        ui->comboBox_2->setVisible(true);
        ui->label_2->setVisible(true);

    }
    else if(currentOp.contains("change",Qt::CaseInsensitive))
    {
        ui->comboBox_2->hide();
        ui->label_2->hide();
        ui->label_3->setText("Old Column_name");
        ui->label_4->setText("New Column_name");
        ui->label_5->setText("New Properties");
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(true);
        ui->lineEdit->setVisible(true);
        ui->lineEdit_2->setVisible(true);
        ui->lineEdit_3->setVisible(true);
    }
    else if(currentOp.contains("rename",Qt::CaseInsensitive))
    {
        ui->label_2->hide();
        ui->comboBox_2->hide();
        ui->label_3->setText("Table_name");
        ui->label_3->setVisible(true);
        ui->lineEdit->setVisible(true);
        ui->label_4->hide();
        ui->lineEdit_2->hide();
        ui->label_5->hide();
        ui->lineEdit_3->hide();
    }
    //resetInputRemind();

}



void tableAlter::TypeChangedSlot(QString currentType)
{
    if(ui->comboBox->currentText().contains("add",Qt::CaseInsensitive))
    {
        if(currentType.contains("column",Qt::CaseInsensitive))
        {
            ui->label_3->setText("Column_name:");
            ui->label_4->setText("Properties:");
            ui->label_5->setText("Comment:");
            ui->label_2->setVisible(true);
            ui->comboBox_2->setVisible(true);
            ui->label_3->setVisible(true);
            ui->lineEdit->setVisible(true);
            ui->label_4->setVisible(true);
            ui->label_5->setVisible(true);
            ui->lineEdit_2->setVisible(true);
            ui->lineEdit_3->setVisible(true);
        }
        else if(currentType.contains("index",Qt::CaseInsensitive))
        {
            ui->label_3->setText("Index_name");
            ui->label_4->setText("column_name");
            ui->label_4->setVisible(true);
            ui->lineEdit_2->setVisible(true);

            ui->label_2->setVisible(true);
            ui->comboBox_2->setVisible(true);
            ui->label_3->setVisible(true);
            ui->lineEdit->setVisible(true);
            ui->label_4->setVisible(true);
            ui->lineEdit_2->setVisible(true);
            ui->label_5->hide();
            ui->lineEdit_3->hide();
        }
        else if(currentType.contains("constraint",Qt::CaseInsensitive))
        {
            ui->label_3->setText("Constraint_name");
            ui->label_4->setText("Constraint");
            ui->label_2->setVisible(true);
            ui->comboBox_2->setVisible(true);
            ui->label_3->setVisible(true);
            ui->lineEdit->setVisible(true);
            ui->label_4->setVisible(true);
            ui->lineEdit_2->setVisible(true);
            ui->label_5->hide();
            ui->lineEdit_3->hide();
        }
        else if(currentType.contains("unique",Qt::CaseInsensitive))
        {
            ui->label_3->setText("Index_name");
            ui->label_4->setText("Column_name");
            ui->label_2->setVisible(true);
            ui->comboBox_2->setVisible(true);
            ui->label_3->setVisible(true);
            ui->lineEdit->setVisible(true);
            ui->label_4->setVisible(true);
            ui->lineEdit_2->setVisible(true);
            ui->label_5->hide();
            ui->lineEdit_3->hide();
        }
        else if(currentType.contains("primary key",Qt::CaseInsensitive))
        {
            ui->label_2->setVisible(true);
            ui->comboBox_2->setVisible(true);
            ui->label_3->setText("Column_name");
            ui->label_4->hide();
            ui->lineEdit_2->hide();
            ui->label_5->hide();
            ui->lineEdit_3->hide();
        }

    }
    else if (ui->comboBox->currentText().contains("drop",Qt::CaseInsensitive))
    {
        if(currentType.contains("index",Qt::CaseInsensitive))
        {
            ui->label_3->setText("Index_name");
            ui->label_4->hide();
            ui->lineEdit_2->hide();
            ui->label_5->hide();
            ui->lineEdit_3->hide();
        }
        else if(currentType.contains("Column",Qt::CaseInsensitive))
        {
            ui->label_3->setText("Column_name");
            ui->label_4->hide();
            ui->lineEdit_2->hide();
            ui->label_5->hide();
            ui->lineEdit_3->hide();
        }
        else if(currentType.contains("primary key",Qt::CaseInsensitive))
        {
            ui->label_3->hide();
            ui->lineEdit->hide();
            ui->label_4->hide();
            ui->lineEdit_2->hide();
            ui->label_5->hide();
            ui->lineEdit_3->hide();
        }
    }
    else if(ui->comboBox->currentText().contains("change",Qt::CaseInsensitive))
    {
        /*if(currentType.contains("Column",Qt::CaseInsensitive))
        {
            ui->label_3->setText("Column_name:");
            ui->label_4->setText("Properties:");
            ui->label_5->setText("Comment:");
            ui->label_4->setVisible(true);
            ui->label_5->setVisible(true);
            ui->lineEdit_2->setVisible(true);
            ui->lineEdit_3->setVisible(true);
        }*/
    }
    else if(ui->comboBox->currentText().contains("rename",Qt::CaseInsensitive))
    {
        /*ui->label_2->hide();
        ui->comboBox_2->hide();
        ui->label_3->setText("Table_name");
        ui->label_4->hide();
        ui->lineEdit_2->hide();
        ui->label_5->hide();
        ui->lineEdit_3->hide();*/
    }
}

QString tableAlter::getInput()
{
    QString input;
    QString cb1 =ui->comboBox->currentText(),
            cb2 =ui->comboBox_2->currentText(),
            le1 =ui->lineEdit->text(),
            le2 =ui->lineEdit_2->text(),
            le3 =ui->lineEdit_3->text();
    if(cb1.contains("add",Qt::CaseInsensitive))
    {
        input +="add ";
        if(cb2.contains("column",Qt::CaseInsensitive))
        {
            input +=le1 +" "+le2+" "+ui->label_5->text() +" "+le3;
        }
        else if(cb2.contains("index",Qt::CaseInsensitive))
        {
            input +=cb2 +" ";
            input +=le1 +"("+le2+")";
        }
        else if(cb2.contains("unique",Qt::CaseInsensitive))
        {
            input +=cb2 +" ";
            input +=le1 +"("+le2+")";
        }
        else if(cb2.contains("constraint",Qt::CaseInsensitive))
        {
            input +=cb2 +" ";
            input +=le1 +" "+le2+" ";
        }
        else if(cb2.contains("primary key",Qt::CaseInsensitive))
        {
            input +=cb2 +"(";
            input +=le1 +")";
        }
    }
    else if(cb1.contains("drop",Qt::CaseInsensitive))
    {
        input +="drop ";
        input +=cb2 +" ";
        if(!cb2.contains("primary key",Qt::CaseInsensitive))
        {
            input +=le1;
        }
    }
    else if(cb1.contains("change",Qt::CaseInsensitive))
    {
        input +="change ";
        input +=le1+" ";
        input +=le2 +" "+le3;
    }
    else if(cb1.contains("rename",Qt::CaseInsensitive))
    {
        input +="rename ";
        input +=le1;
    }
    return input;
}








