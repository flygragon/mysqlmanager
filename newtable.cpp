#include "newtable.h"
#include "ui_newtable.h"
#include <QDebug>

NewTable::NewTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTable)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(addColumn()),Qt::AutoConnection);
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(delColumn()),Qt::AutoConnection);
}

NewTable::~NewTable()
{
    delete ui;
}

void NewTable::addColumn()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() +1);
}


void NewTable::delColumn()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

std::vector<QStringList> NewTable::getInput()
{
    std::vector<QStringList> input;
    QStringList tmp;
    for (int i =0;i <ui->tableWidget->rowCount();i ++)
    {
        tmp.clear();
        QTableWidgetItem *p0 =ui->tableWidget->item(i,0),
                     *p1 =ui->tableWidget->item(i,1),
                     *p2 =ui->tableWidget->item(i,2),
                     *p3 =ui->tableWidget->item(i,3),
                     *p4 =ui->tableWidget->item(i,4),
                     *p5 =ui->tableWidget->item(i,5);
        if(p0 ==nullptr || p1 ==nullptr)
        {
            QMessageBox::warning(this,"Input Error","field name or type empty");
            return std::vector<QStringList>();
        }
        tmp +=p0->text();
        tmp +=p1->text();
        if(p2!=nullptr && p2->text().contains("N",Qt::CaseInsensitive))
                tmp +="not null";
        if(p3!=nullptr &&(p3->text().contains("pr",Qt::CaseInsensitive)
                ||p3->text().contains("pk",Qt::CaseInsensitive)))
            tmp +="primary key";
        if(p5!= nullptr &&!p5->text().isEmpty())
            tmp +=p5->text();
        if(p4 !=nullptr &&!p4->text().isEmpty())
        {
            QString defaul ="default ";
            bool isStr =!p1->text().isEmpty() && (p1->text().contains("char",Qt::CaseInsensitive)
                    ||p1->text().contains("text",Qt::CaseInsensitive));
            if(isStr)
                defaul +="'";
            defaul +=p4->text();
            if(isStr)
                defaul +="'";
            tmp +=defaul;
        }
        input.push_back(tmp);

        if(p3!=nullptr &&!p3->text().isEmpty() &&(p3->text().contains("fk",Qt::CaseInsensitive)
                ||p3->text().contains("fri",Qt::CaseInsensitive)
                ||p3->text().contains("foreign key",Qt::CaseInsensitive)))
        {
            if(p3->text().contains("(")
                    && p3->text().contains(")"))
            {
                QString fk ="foreign key(";
                fk +=p0->text();
                fk +=") references ";
                int pos1 =p3->text().lastIndexOf(')'),
                        pos2 =p3->text().lastIndexOf('(',pos1);
                if(pos1 ==-1||pos2 ==-1)
                {
                    QMessageBox::warning(this,"Input Error","foreign key references foreigntable(field_name)");
                    return std::vector<QStringList>();
                }
                int i =pos2 -1;
                while (i >=0 && p3->text()[i] ==' ')
                    --i;
                if(i <0)
                {
                    QMessageBox::warning(this,"Input Error","foreign key references foreigntable(field_name)");
                    return std::vector<QStringList>();
                }
                int j =p3->text().lastIndexOf(' ',i);
                if(j ==-1)
                    j =0;
                fk +=p3->text().mid(j,i-j+1);

                fk +=p3->text().mid(pos2,pos1-pos2+1);
                input.push_back(QStringList()<<fk);
            }
        }
    }
    qDebug()<<input.back();
    input.push_back(QStringList()<<ui->lineEdit->text());
    qDebug()<<input;
    return input;
}


