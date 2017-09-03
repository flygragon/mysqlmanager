#include "mysql.h"
#include <QDebug>
#include <iostream>
#include <string>
#include <vector>
#include<assert.h>
mysql::mysql(QString&connName,QString& HostName,QString& port,QString& UserName,QString& PassWord)
{
    queryResult =nullptr;
    tableResult =nullptr;
    thisdb =QSqlDatabase::addDatabase("QMYSQL3",connName);
    thisdb.setHostName(HostName);
    thisdb.setPort(port.toInt());
    //thisdb.setDatabaseName("testdb");
    if(!thisdb.open(UserName,PassWord))
    {
        err =thisdb.lastError();
        //thisdb.QSqlDatabase();
        thisdb.close();
        QSqlDatabase::removeDatabase(connName);
        qDebug()<<"MySQL connection Failed!\n"<<UserName<<"Login Failed\n";
        QMessageBox::warning(0,"Connection","Connection Failed!");
    }
    else qDebug()<<"MySQL connection Succeed!\n"<<UserName<<"Login Succeed!\n";
}

 mysql::~mysql(){
     //qDebug()<<"Exiting";
     //query("\\q");

    delete queryResult;
     delete tableResult;
}

void mysql::query(const char* queryStr)
{
        if(!thisdb.isOpen())
        {
            QMessageBox::warning(0,"mysql Query Error!","No Connection!");
            return;
        }
        qDebug()<<"11\n";
        QSqlQuery currquery(thisdb);
        qDebug()<<"22\n";
        if(queryResult)
            delete queryResult;
        qDebug()<<"33\n";
        queryResult =new std::vector<QString>;
        assert(queryResult!=nullptr);
        if(!currquery.exec(queryStr))
        {
            queryValid =false;
            qDebug()<<currquery.lastError().text();
            QMessageBox::warning(0,"Sql Error",currquery.lastError().text());
            return;
        }
        queryValid =true;
        while(currquery.next())
        {
            queryResult->push_back(currquery.value(0).toString());
        }
}

bool mysql::isOpen()
{
    return this->thisdb.isOpen();
}

void mysql::tableQuery(const char *queryStr)
{
    if(!thisdb.isOpen())
    {
        QMessageBox::warning(0,"Query Error!","No Connection!");
        return;
    }
    qDebug()<<"44\n";
    QSqlQuery currquery(thisdb);
    qDebug()<<"55\n";
    if(tableResult)
        delete tableResult;
    qDebug()<<"66\n";
    tableResult =new std::vector<std::vector<QString>>;
    qDebug()<<"77";
    assert(queryResult!=nullptr);
    qDebug()<<"88";
    if(!currquery.exec(queryStr))
    {
        QMessageBox::warning(0,"Sql Error",currquery.lastError().text());
        qDebug()<<"Sql Query Failed";
        queryValid =false;
        return;
    }
    std::vector<QString>tmp;
    queryValid =true;
    qDebug()<<currquery.lastError().type();
    /*if(!currquery.isValid())
    {
        qDebug()<<"Invalid SqlQuery";
        qDebug()<<currquery.lastError().text();
        return;
    }*/
    while(currquery.next()) {
        tmp.clear();
        //qDebug()<<"1010";
        for(int i =0;currquery.value(i).isValid();i ++) {
            //qDebug()<<"1111";
            //qDebug()<<currquery.value(i).toString();
            tmp.push_back(currquery.value(i).toString());
        }
        tableResult->push_back(tmp);
    }
}
bool mysql::lastQueryValid()
{
    return queryValid;
}
