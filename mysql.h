#ifndef MYSQL_H
#define MYSQL_H
#include<QtSql>
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QString>
#include<QMessageBox>
#include<vector>

class mysql
{
public:
    //mysql();
    mysql(QString& connName,QString& HostName,QString& port,QString& UserName,QString& PassWord);
    ~mysql();
    void query(const char* queryStr);
    void tableQuery(const char* queryStr);
    std::vector<QString>* queryResult;
    std::vector<std::vector<QString>> *tableResult;
    bool isOpen();
    bool lastQueryValid();
private:
    QSqlDatabase thisdb;
    QSqlError err;
    bool queryValid;
};

#endif // MYSQL_H
