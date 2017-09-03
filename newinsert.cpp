#include "newinsert.h"
#include "ui_newinsert.h"
#include <QDebug>

NewInsert::NewInsert(QWidget *parent)
{

}


NewInsert::NewInsert(QWidget *parent,std::vector<std::vector<QString>>&tableInfo) :
    QDialog(parent),
    ui(new Ui::NewInsert)
{
    ui->setupUi(this);
    tableDescribe =tableInfo;
    QStringList tableHeader;
    qDebug()<<"Creating Headers";
    qDebug()<<tableDescribe;
    for(auto&val:tableDescribe)
        tableHeader<<val[0];
    qDebug()<<"Setting Headers";
    qDebug()<<tableHeader;
    ui->tableWidget->setColumnCount(tableHeader.size());
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(addTableItem()),Qt::AutoConnection);
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(delTableItem()),Qt::AutoConnection);
    qDebug()<<"NewInsert Dialog Created";
}

NewInsert::~NewInsert()
{
    delete ui;
}

void NewInsert::addTableItem()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
}

void NewInsert::delTableItem()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}


std::vector<QStringList> NewInsert::getInput()
{
    std::vector<QStringList> queries;
    QString fields,values;
    QTableWidgetItem* pItem;
    bool isStr;
    for(int i =0;i <ui->tableWidget->rowCount();i++)
    {
        for(int j =0;j <ui->tableWidget->colorCount();j++)
        {
            pItem =ui->tableWidget->item(i,j);
            if(pItem!=nullptr && !pItem->text().isEmpty())
            {
                fields +=tableDescribe[j][0];
                fields +=",";
                isStr =tableDescribe[j][1].contains("char",Qt::CaseInsensitive)
                        ||tableDescribe[j][1].contains("text",Qt::CaseInsensitive);
                if(isStr)
                    values +="'";
                values +=pItem->text();
                if(isStr)
                    values +="'";
                values +=",";
            }

        }
        if(fields.isEmpty() && values.isEmpty())
            continue;
        fields.remove(fields.size()-1,1);
        values.remove(values.size()-1,1);
        queries.push_back(QStringList()<<fields<<values);
        fields.clear();
        values.clear();
    }
    return queries;
}
