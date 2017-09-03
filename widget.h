#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include "mysql.h"
#include"createconnection.h"
#include <vector>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMenu>
#include <QAction>
#include "newaddtion.h"
#include <QMouseEvent>
#include <QPoint>
#include <QCursor>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "newuser.h"
#include "modifypasswd.h"
#include "newconnection.h"
#include "additionnew.h"
#include "adduser.h"
#include "resetpwd.h"
#include "deleteuser.h"
#include "newtable.h"
#include "newinsert.h"
#include "tablealter.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget*parent = 0);
    ~Widget();
    void Query( QString& queryStr,int cur);
    void addRoot(QString& rootName);
    void tableQuery(QString& queryStr,int cur);
public slots:
    void addNewConnection();
    void addNewChild(QTreeWidgetItem*,int);
    void newDefaultQuery(QTreeWidgetItem*);
    void treeViewNewSlot();
    void treeViewDeleteSlot();
    void treeViewNewUserSlot();
    void treeViewDropUserSlot();
    void tableViewNewSlot();
    void tableViewDeleteSlot();
    void newEvent();
    void tableViewNewOkSlot();
    void tableViewNewCancelSlot();
    void treeViewPassWdRst();
    //void mousePressEventSlot(QMouseEvent*);


private:
    Ui::Widget *ui;
    AddUser* pnewUser;
    std::vector<mysql*> thisMySql;
    newConnection* newCon;
    std::vector<std::vector<QString>> conInfo;
    //QMenu* rightMouse1,*rightMouse2;
    AdditionNew* add;
    resetPwd* rstPwd;
    DeleteUser* DelUser;
    QTreeWidgetItem* cur,*lastDoubleClicked;
    QAction*rm11,*rm12,*rm13,*rm14,*rm15,*rm16,*rm17,*rm18,*rm21,*rm22;
    QMouseEvent *mouse;
    QPoint mousePoint;
    int childrenNums =0;
    int tableConIndex;
    QString tableDBName;
    std::vector<std::vector<QString>> tableDescribe,treeTableDescribe;
    NewTable* pNewTable;
    NewInsert* pNewInsert;
    tableAlter* pTableAlter;
    void tableNewInsert();
    bool insertFromTable =false;

private slots:
    void recvNewUserClosed();
    void recvNewUserOk();
    void recvRstPasswdOk();
    void recvRstPasswdClosed();
    void rcvDelUserOk();
    void rcvDelUserCancel();
    void tableItemChangedSlot(QTableWidgetItem*);
    void tableItemActivatedSlot();
    //void mouseMoveEvent();
    void tableLoseFocus();
    void newTableSlot();
    void newTableOkSLot();
    void newTableCancelSlot();
    void newInsertOkSlot();
    void newInsertCacelSlot();
    void treeViewAlterSlot();
    void tableAlterOkSlot();
    void tableAlterCancelSlot();
    void backupSlot();
    void recoverySlot();

signals:
    void requestFlush(QTreeWidgetItem*);
    void Triggered11(QPoint&curMouse);
    void Triggered12(QPoint&curMouse);
   private slots:
    void getConData();
    void destroyNewCon();
    void doubleClick(QTreeWidgetItem*,int);
    //void closeNewCon();
    void createNewConnection(QString&conName,QString&HostName,QString&port,QString&UserName,QString&Passwd);
    void treeViewNewOkSlot();
    void treeViewNewCancelSlot();
    void get11Point();
    void get12Point();
    //void mousePressEvent(QMouseEvent*);
    void on_pushButton_2_clicked();
};

#endif // WIDGET_H
