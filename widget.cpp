#include "widget.h"
#include "ui_widget.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QModelIndex>
#include <QFileDialog>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    /*mysql* tmpMySql =new (std::nothrow)mysql("Connection","127.0.0.1","3306","testuser","testuserpasswd");
    thisMySql.push_back(tmpMySql);*/
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel("Connection");
    ui->treeWidget->setAutoScroll(true);
    connect(this->ui->pushButton,SIGNAL(clicked()),this,SLOT(addNewConnection()),Qt::UniqueConnection);
    //rightMouse1 =new QMenu(ui->treeWidget);
    //rightMouse2 =new QMenu(ui->tableWidget);
    lastDoubleClicked =nullptr;
    cur=nullptr;
    pnewUser =nullptr;
    rstPwd =nullptr;
    add =nullptr;
    rm11 =new QAction("New",ui->treeWidget),
    rm12 =new QAction("Delete",ui->treeWidget),
    rm13 =new QAction("Add User",ui->treeWidget),
    rm14 =new QAction("Drop/Delete User",ui->treeWidget),
    rm15 =new QAction("Reset Passwd",ui->treeWidget),
    rm16 =new QAction("Alter",ui->treeWidget),
    rm18 =new QAction("Recovery",ui->treeWidget),
    rm17 =new QAction("Backup",ui->treeWidget),
    rm21 =new QAction("New",ui->tableWidget),
    rm22 =new QAction("Delete",ui->tableWidget);
    //rm11->setDisabled(true);
    ui->treeWidget->addAction(rm11);
    ui->treeWidget->addAction(rm12);
    ui->treeWidget->addAction(rm16);
    ui->treeWidget->addAction(rm17);
    ui->treeWidget->addAction(rm18);
    ui->treeWidget->addAction(rm13);
    ui->treeWidget->addAction(rm14);
    ui->treeWidget->addAction(rm15);
    ui->tableWidget->addAction(rm21);
    ui->tableWidget->addAction(rm22);
    ui->treeWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
    //connect(rm11,SIGNAL(triggered()),this,SLOT(get11Point()),Qt::UniqueConnection);
    //connect(rm12,SIGNAL(triggered()),this,SLOT(get12Point()),Qt::UniqueConnection);
    connect(rm11,SIGNAL(triggered()),this,SLOT(treeViewNewSlot()),Qt::UniqueConnection);
    connect(rm12,SIGNAL(triggered()),this,SLOT(treeViewDeleteSlot()),Qt::UniqueConnection);
    connect(rm13,SIGNAL(triggered()),this,SLOT(treeViewNewUserSlot()),Qt::UniqueConnection);
    connect(rm14,SIGNAL(triggered()),this,SLOT(treeViewDropUserSlot()),Qt::UniqueConnection);
    connect(rm15,SIGNAL(triggered()),this,SLOT(treeViewPassWdRst()),Qt::UniqueConnection);
    connect(rm16,SIGNAL(triggered()),this,SLOT(treeViewAlterSlot()),Qt::AutoConnection);
    connect(rm17,SIGNAL(triggered()),this,SLOT(backupSlot()),Qt::AutoConnection);
    connect(rm18,SIGNAL(triggered()),this,SLOT(recoverySlot()),Qt::AutoConnection);
    connect(rm21,SIGNAL(triggered()),this,SLOT(tableViewNewSlot()),Qt::UniqueConnection);
    connect(rm22,SIGNAL(triggered()),this,SLOT(tableViewDeleteSlot()),Qt::UniqueConnection);
    //connect(ui->tableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(tableItemChangedSlot(QTableWidgetItem*)),Qt::AutoConnection);
    mouse =new QMouseEvent(QEvent::MouseButtonPress,mousePoint,Qt::RightButton,Qt::RightButton,Qt::NoModifier);
    connect(ui->tableWidget,SIGNAL(itemSelectionChanged()),this,SLOT(tableItemActivatedSlot()),Qt::UniqueConnection);
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()),Qt::UniqueConnection);
}

Widget::~Widget()
{
    delete ui;
    for(auto&v:thisMySql)
    delete v;
}
void Widget::Query(QString& queryStr,int cur)
{
    if(thisMySql.empty() || cur>=thisMySql.size() ||cur<0)
    {
        QMessageBox::warning(0,"Widget Query Error!","No Connection!");
    }
    else  {
        thisMySql[cur]->query(queryStr.toStdString().c_str());
        for (int i =0,len =thisMySql[cur]->queryResult->size();i <len;i ++)
        qDebug()<<(thisMySql[cur]->queryResult->at(i))<<'\n';
    }
}
void Widget::addNewConnection()
{
    qDebug()<<"Create New Connection";
    //newCon =new createConnection();
    //newCon->setWindowFlags(Qt::FramelessWindowHint);
    tableLoseFocus();
    newCon =new newConnection(this);
    newCon->open();
    childrenNums ++;
    //newCon->setWindowModality(Qt::ApplicationModal);
    //this->setDisabled(true);
    qDebug()<<"NewCon Shown";
    connect(this->newCon,SIGNAL(accepted()),this,SLOT(getConData()),Qt::UniqueConnection);
    connect(this->newCon,SIGNAL(rejected()),this,SLOT(destroyNewCon()),Qt::UniqueConnection);
    //connect(this,SIGNAL(closeNewCon()),this->newCon,SLOT(close()),Qt::UniqueConnection);
}
void Widget::getConData()
{
    conInfo.push_back(newCon->getConInfo());
    for(QString& v:conInfo.back())
    qDebug()<<v;
    createNewConnection(conInfo.back().at(0),conInfo.back().at(1),conInfo.back().at(2),conInfo.back().at(3),conInfo.back().at(4));

}
void Widget::createNewConnection(QString &conName, QString &HostName, QString &port, QString &UserName, QString &Passwd)
{
    mysql*tmpMySql =new mysql(conName,HostName,port,UserName,Passwd);

    destroyNewCon();
    if (!tmpMySql->isOpen()) {
        delete tmpMySql;
        conInfo.pop_back();
        return;
    }
    thisMySql.push_back(tmpMySql);
    addRoot(conName);
}
void Widget::addRoot(QString &rootName)
{
    QTreeWidgetItem* tmp =new QTreeWidgetItem(QStringList(rootName));
    //tmp->setFont(1,);
    ui->treeWidget->addTopLevelItem(tmp);
    connect(ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(doubleClick(QTreeWidgetItem*,int)),Qt::UniqueConnection);
    connect(this,SIGNAL(requestFlush(QTreeWidgetItem*)),this,SLOT(newDefaultQuery(QTreeWidgetItem*)),Qt::UniqueConnection);

}

void Widget::newDefaultQuery(QTreeWidgetItem *curItem)
{
    int conIndex;
    QString tmp;
    if (curItem->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(curItem);
        tmp ="show databases";
        Query(tmp,conIndex);
        for (int i =0,cnt =curItem->childCount();i <cnt;i ++)
        curItem->removeChild(curItem->child(0));
        addNewChild(curItem,conIndex);

    }
    else if(curItem->parent()->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(curItem->parent());
        QString tmp ="use ";
        tmp +=curItem->text(0);
        Query(tmp,conIndex);
        tmp ="show tables";
        Query(tmp,conIndex);
        for (int i =0,cnt =curItem->childCount();i <cnt;i ++)
        curItem->removeChild(curItem->child(0));
        addNewChild(curItem,conIndex);
    }
    else if (curItem->parent()->parent()->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(curItem->parent()->parent());
        tmp ="use ";
        tmp +=curItem->parent()->text(0);
        tableQuery(tmp,conIndex);
        tmp ="describe ";
        tmp +=curItem->text(0);
        qDebug()<<tmp;
        tableQuery(tmp,conIndex);
        tableDescribe =*(thisMySql[conIndex]->tableResult);
        //ui->tableWidget->setWindowTitle(curItem->text(0));
        //if (thisMySql[conIndex]->lastQueryValid())
        //{
        QStringList header;
        for (auto&val:tableDescribe)
            header +=val[0];
        ui->tableWidget->setColumnCount(thisMySql[conIndex]->tableResult->size());
        ui->tableWidget->setHorizontalHeaderLabels(header);
        ui->tableWidget->setWindowTitle(curItem->text(0));
        ui->tableWidget->show();
        tableConIndex =conIndex;
        tableDBName =curItem->parent()->text(0);
        //}
        //qDebug()<<ui->tableWidget->columnCount();
        //QString l =header.join(",");
         //   qDebug()<<l;
        tmp ="select * from ";
        tmp +=curItem->text(0);
        tableQuery(tmp,conIndex);
        qDebug()<<thisMySql[conIndex]->tableResult->size();
        ui->tableWidget->setRowCount(thisMySql[conIndex]->tableResult->size());
        for (int i =0,len =thisMySql[conIndex]->tableResult->size();i<len;i ++)
            for (int j =0,l =thisMySql[conIndex]->tableResult->at(i).size();j <l;j ++)
                ui->tableWidget->setItem(i,j,new QTableWidgetItem((*(thisMySql[conIndex]->tableResult))[i][j]));
    }
    qDebug()<<conIndex;
}

void Widget::addNewChild(QTreeWidgetItem* parent,int conIndex)
{
    QTreeWidgetItem* tmp;
    for(auto&v: *(thisMySql[conIndex]->queryResult))
    {
    tmp =new QTreeWidgetItem(QStringList(v));
    parent->addChild(tmp);
    }
}
void Widget::doubleClick(QTreeWidgetItem *curItem, int col)
{
    tableLoseFocus();
    int conIndex;
    cur =ui->treeWidget->currentItem();
    if(cur->parent()==nullptr)
        conIndex=ui->treeWidget->indexOfTopLevelItem(cur);
    else if (cur->parent()->parent()==nullptr)
        conIndex=ui->treeWidget->indexOfTopLevelItem(cur->parent());
    else
        conIndex=ui->treeWidget->indexOfTopLevelItem(cur->parent()->parent());

    QString tmp =conInfo[conIndex][3];
    ui->label_3->setText(tmp);
    tmp =conInfo[conIndex][0];
    tmp +=" to:";
    tmp +=conInfo[conIndex][1];
    tmp +=":";
    tmp +=conInfo[conIndex][2];
    ui->label_4->setText(tmp);

    if (curItem->parent()&&curItem->parent()->parent())
        lastDoubleClicked =curItem;
    if (curItem->childCount() ==0 || !curItem->isExpanded())
        emit requestFlush(curItem);
}
void Widget::tableQuery(QString &queryStr, int cur)
{
    if(thisMySql.empty() || cur>=thisMySql.size() ||cur <0)
    {
        QMessageBox::warning(0,"Widget Query Error!","No Connection!");
    }
    else  {
        thisMySql[cur]->tableQuery(queryStr.toStdString().c_str());
        qDebug()<<"tableQuery completed";
        //if (thisMySql[cur]->lastQueryValid()) {
            qDebug()<<"Get Table Result";
        for (auto&v :*(thisMySql[cur]->tableResult))

                qDebug()<<v;

        //}
        //else
        //qDebug()<<"this Query Got Nothing";
    }
}

void Widget::destroyNewCon()
{
    newCon->close();
    delete newCon;
    newCon =nullptr;
    if(--childrenNums ==0)
        this->setEnabled(true);
}

void Widget::treeViewNewSlot()
{
    /*qDebug()<<click;
    if (ui->treeWidget->itemAt(click) ==nullptr)
    {
        qDebug()<<click<<"No WidgetItem";
        return;
    }*/
    tableLoseFocus();
    cur= ui->treeWidget->currentItem();
    if (cur ==nullptr)
    {
        qDebug()<<"No Current Item";
        return ;
        }
    if(cur->parent() ==nullptr)
    {
        add =new AdditionNew(this);
        QString tmp ="DB Name:";
        add->setUiLabelText(tmp);

        //add ->setWindowFlags(Qt::FramelessWindowHint);
        add->open();
        childrenNums++;
        //add->setWindowModality(Qt::ApplicationModal);
        //this->setDisabled(true);
        connect(add,SIGNAL(accepted()),this,SLOT(treeViewNewOkSlot(QString&)),Qt::UniqueConnection);
        connect(add,SIGNAL(rejected()),this,SLOT(treeViewNewCancelSlot()),Qt::UniqueConnection);
    }
    else if (cur->parent()->parent()==nullptr)
    {
  /*      add =new AdditionNew(this);
        QString tmp ="Sql Input:";
        add->setUiLabelText(tmp);
        //add ->setWindowFlags(Qt::FramelessWindowHint);
        add->open();
        childrenNums++;
        //add->setWindowModality(Qt::ApplicationModal);
        //this->setDisabled(true);
        connect(add,SIGNAL(accepted()),this,SLOT(treeViewNewOkSlot()),Qt::UniqueConnection);
        connect(add,SIGNAL(rejected()),this,SLOT(treeViewNewCancelSlot()),Qt::UniqueConnection);
*/
        QString SQLquery ="use ";
        int conIndex =ui->treeWidget->indexOfTopLevelItem(cur->parent());
        SQLquery +=cur->text(0);
        Query(SQLquery,conIndex);
        newTableSlot();
    }
    else if (cur->parent()->parent()->parent() ==nullptr)
    {
        lastDoubleClicked =cur;
        insertFromTable =false;
        qDebug()<<"Insert from treeWidget";
        tableNewInsert();
    }
}
void Widget::treeViewNewOkSlot()
{
    QString input =add->getInput();
    if (input.isEmpty())
    {
        add->close();
        delete add;
        if(--childrenNums==0)
            this->setEnabled(true);
        return;
    }
    QString query;
    int conIndex;
    if (cur->parent()==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur);
        query +="create database ";
        query +=input;
        add->close();
        delete add;
        if(--childrenNums==0);
        Query(query,conIndex);
        query ="show databases";
        Query(query,conIndex);
        for (int i =0,cnt =cur->childCount();i <cnt;i ++)
        cur->removeChild(cur->child(0));
        addNewChild(cur,conIndex);
    }
    else if (cur ->parent()->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur->parent());
        query +="use ";
        query +=cur->text(0);
        Query(query,conIndex);
        Query(input,conIndex);
        add->close();
        delete add;
        if(--childrenNums==0);
        query ="show tables";
        Query(query,conIndex);
        for (int i =0,cnt =cur->childCount();i <cnt;i ++)
        cur->removeChild(cur->child(0));
        addNewChild(cur,conIndex);

    }
}

void Widget::treeViewNewCancelSlot()
{
    add->close();
    delete add;
    if(--childrenNums==0);
}

void Widget::treeViewDeleteSlot()
{
    /*qDebug()<<click;
    if(ui->treeWidget->itemAt(click) ==nullptr)
    {
        qDebug()<<click<<"No WidgetItem";
        return;
    }*/
    tableLoseFocus();
    cur =ui->treeWidget->currentItem();
    if (cur ==nullptr)
    {
        qDebug()<<"No Current Item";
        return;
    }
    int conIndex;
    if (cur ->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur);
        delete thisMySql[conIndex];
        qDebug()<<"deleted";
        thisMySql.erase(thisMySql.begin()+conIndex);
        qDebug()<<"erased";
        if(conIndex ==ui->treeWidget->indexOfTopLevelItem(lastDoubleClicked))
            lastDoubleClicked =nullptr;
        ui->treeWidget->removeItemWidget(cur,0);
        qDebug()<<"Root Removed";
        ui->treeWidget->takeTopLevelItem(conIndex);
        qDebug()<<"Root treeWidget Clear";

        if(conIndex ==tableConIndex)
        {
            ui->tableWidget->clear();
            ui->tableWidget->setRowCount(0);
            ui->tableWidget->setWindowTitle("");
            tableConIndex =-1;
            tableDBName ="";
        }
        else if (conIndex<tableConIndex)
        {
            --tableConIndex;
        }
    }
    else if (cur->parent()->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur->parent());
        QString tmp ="drop database ";
        QString tmp1 =cur->text(0);
        tmp +=cur->text(0);
        Query(tmp,conIndex);
        tmp ="show databases";
        Query(tmp,conIndex);
        QTreeWidgetItem* curParent =cur->parent();
        for (int i =0,cnt =curParent->childCount();i <cnt;i ++)
        curParent->removeChild(curParent->child(0));
        addNewChild(curParent,conIndex);
        if(thisMySql[conIndex]->lastQueryValid())
        {
            if(conIndex<tableConIndex)
                --tableConIndex;
            else if(conIndex ==tableConIndex && tmp1 ==tableDBName)
            {
                ui->tableWidget->clear();
                ui->tableWidget->setRowCount(0);
                ui->tableWidget->setWindowTitle("");
                tableConIndex =-1;
                tableDBName ="";
            }
        }


    }
    else if (cur->parent()->parent()->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur->parent()->parent());
        QString tmp ="use  ";
        tmp +=cur->parent()->text(0);
        Query(tmp,conIndex);
        if(cur ==lastDoubleClicked)
        lastDoubleClicked =nullptr;
        tmp ="drop table ";
        tmp +=cur->text(0);
        QString tmp1 =cur->parent()->text(0),
                tmp2=cur->text(0);
        Query(tmp,conIndex);
        tmp ="show tables";
        Query(tmp,conIndex);
        QTreeWidgetItem* curParent =cur->parent();
        for (int i =0,cnt =curParent->childCount();i <cnt;i ++)
        curParent->removeChild(curParent->child(0));
        addNewChild(curParent,conIndex);
        if(conIndex <tableConIndex)
            --tableConIndex;
        else if(conIndex ==tableConIndex && tmp1 ==tableDBName && tmp2 ==ui->tableWidget->windowTitle())
        {
            ui->tableWidget->clear();
            ui->tableWidget->setRowCount(0);
            ui->tableWidget->setWindowTitle("");
            tableConIndex =-1;
            tableDBName ="";
        }
    }
}

void Widget::tableViewNewSlot()
{
    if(lastDoubleClicked ==nullptr)
        return;
    tableLoseFocus();
    insertFromTable =true;
    tableNewInsert();

    //connect(add,SIGNAL(okSignal(QString&)),this,SLOT(tableViewNewOkSlot(QString&)),Qt::UniqueConnection);
    //connect(add,SIGNAL(cancelSignal()),this,SLOT(tableViewNewCancelSlot()),Qt::UniqueConnection);
}

void Widget::tableViewDeleteSlot()
{
    tableLoseFocus();
    if(lastDoubleClicked ==nullptr)
        return;
    QTableWidgetItem* curTableItem =ui->tableWidget->currentItem();
    if(curTableItem ==nullptr)
        return;
    int rowNum =curTableItem->row();
    qDebug()<<"Row No. "<<rowNum;
    QString SQLquery;
    bool isStr;
    SQLquery ="use ";
    SQLquery +=tableDBName;
    Query(SQLquery,tableConIndex);
    SQLquery ="delete from ";
    SQLquery +=ui->tableWidget->windowTitle() +" where ";
    qDebug()<<"Start getting table data";
    for(int j =0;j<ui->tableWidget->columnCount();j++)
    {
        //qDebug()<<"Getting Column "<<j;
        SQLquery +=ui->tableWidget->horizontalHeaderItem(j)->text();
        if(ui->tableWidget->item(rowNum,j) ==nullptr||ui->tableWidget->item(rowNum,j)->text().isEmpty())
            SQLquery +=" is null";
        else
        {
            isStr =tableDescribe[j][1].contains("text",Qt::CaseInsensitive) || tableDescribe[j][1].contains("char",Qt::CaseInsensitive);
            SQLquery +=" = ";
            if(isStr)
                SQLquery +="'";
            SQLquery +=ui->tableWidget->item(rowNum,j)->text();
            if(isStr)
                SQLquery +="'";
        }
        SQLquery +=" and ";
        //qDebug()<<"Got Column "<<j;
    }
    qDebug()<<"Got table data";
    SQLquery.remove(SQLquery.size()-5,5);
    Query(SQLquery,tableConIndex);
    if(!thisMySql[tableConIndex]->lastQueryValid())
        return;
    qDebug()<<"Requery table";
    SQLquery="select * from ";
    SQLquery +=ui->tableWidget->windowTitle();
    tableQuery(SQLquery,tableConIndex);
    if(!thisMySql[tableConIndex]->lastQueryValid())
        return;
    qDebug()<<"Reflushing table";
    //ui->tableWidget->clear();
    //ui->tableWidget->setColumnCount(tableDescribe.size());
    ui->tableWidget->setRowCount(thisMySql[tableConIndex]->tableResult->size());
    qDebug()<<"Table resized";
    for (int i =0,len =thisMySql[tableConIndex]->tableResult->size();i<len;i ++)
        for (int j =0,l =thisMySql[tableConIndex]->tableResult->at(i).size();j <l;j ++)
        {
            qDebug()<<"New Row "<<i;
            ui->tableWidget->setItem(i,j,new QTableWidgetItem((*(thisMySql[tableConIndex]->tableResult))[i][j]));
            qDebug()<<"Inserted";
        }
    //connect(add,SIGNAL(accepted()),this,SLOT(tableViewNewOkSlot()),Qt::UniqueConnection);
    //connect(add,SIGNAL(rejected()),this,SLOT(tableViewNewCancelSlot()),Qt::UniqueConnection);
}

void Widget::newEvent()
{
    add =new AdditionNew(this);
    QString tmp ="Sql Input:";
    add->setUiLabelText(tmp);
    //add ->setWindowFlags(Qt::FramelessWindowHint);
    add->open();
    childrenNums++;
    //add->setWindowModality(Qt::ApplicationModal);
    //this->setDisabled(true);
}

void Widget::tableViewNewOkSlot()
{
    QString input =add->getInput();
    int conIndex =ui->treeWidget->indexOfTopLevelItem(lastDoubleClicked->parent()->parent());
    QString tmp ="use ";
    tmp +=lastDoubleClicked->parent()->text(0);
    Query(tmp,conIndex);
    tableQuery(input,conIndex);
    tableViewNewCancelSlot();
    tmp ="select * from ";
    tmp +=lastDoubleClicked->text(0);
    tableQuery(tmp,conIndex);
    ui->tableWidget->setRowCount(thisMySql[conIndex]->tableResult->size());
    for (int i =0,len =thisMySql[conIndex]->tableResult->size();i<len;i ++)
        for (int j =0,l =thisMySql[conIndex]->tableResult->at(i).size();j <l;j ++)
            ui->tableWidget->setItem(i,j,new QTableWidgetItem((*(thisMySql[conIndex]->tableResult))[i][j]));
}

void Widget::tableViewNewCancelSlot()
{
    add->close();
    delete add;
    if(--childrenNums==0);
}

void Widget::get11Point()
{
    mousePoint =ui->treeWidget->mapFromGlobal(this->cursor().pos());
    emit Triggered11(mousePoint);
}

void Widget::get12Point()
{
    mousePoint =ui->treeWidget->mapFromGlobal(this->cursor().pos());
    emit Triggered12(mousePoint);
}

/*void Widget::mousePressEvent(QMouseEvent *mouse)
{
    QModelIndex index =ui->treeWidget->indexAt(mouse->pos());
    if(!index.isValid())//treeWidgetItem失去焦点
        ui->treeWidget->clearFocus();
}*/

void Widget::treeViewNewUserSlot()
{
    tableLoseFocus();
    cur =ui->treeWidget->currentItem();
    if (cur ==nullptr)
    {
        qDebug()<<"No Current Item";
        return;
    }

    pnewUser =new AddUser(this);
    //pnewUser ->setWindowFlags(Qt::FramelessWindowHint);
    pnewUser->open();
    childrenNums++;
    //pnewUser->setWindowModality(Qt::ApplicationModal);
    //this->setDisabled(true);
    connect(pnewUser,SIGNAL(rejected()),this,SLOT(recvNewUserClosed()),Qt::UniqueConnection);
    connect(pnewUser,SIGNAL(accepted()),this,SLOT(recvNewUserOk()),Qt::UniqueConnection);

}

void Widget::recvNewUserClosed()
{
    delete pnewUser;
    pnewUser =nullptr;
    if(--childrenNums==0);
}

void Widget::recvNewUserOk()
{
    QStringList newUserArgs =pnewUser->getInput();
    qDebug()<<newUserArgs;
    recvNewUserClosed();
    cur =ui->treeWidget->currentItem();
    if (cur ==nullptr)
    {
        qDebug()<<"No Current Item";
        return;
    }
    int conIndex;
    if(cur->parent()==nullptr)
        conIndex=ui->treeWidget->indexOfTopLevelItem(cur);
    else if (cur->parent()->parent()==nullptr)
        conIndex=ui->treeWidget->indexOfTopLevelItem(cur->parent());
    else
        conIndex=ui->treeWidget->indexOfTopLevelItem(cur->parent()->parent());
    QString SQLquery ="create user ";
    SQLquery +=newUserArgs[0];
    SQLquery +="@\"";
    SQLquery +=newUserArgs[2];
    SQLquery +="\"";
    SQLquery +=" identified by \"";
    SQLquery +=newUserArgs[1];
    SQLquery +="\"";
    qDebug()<<SQLquery;
    Query(SQLquery,conIndex);
    //thisMySql[conIndex]->query(SQLquery.toStdString().c_str());
    if(newUserArgs.size() ==5 && thisMySql[conIndex]->lastQueryValid())
    {
        SQLquery ="grant ";
        SQLquery += newUserArgs[3];
        SQLquery +=" on ";
        SQLquery +=newUserArgs[4];
        if(SQLquery.toStdString().find_last_of(".*")==std::string::npos)
            SQLquery +=".*";
        SQLquery +=" to ";
        SQLquery +=newUserArgs[0];
        SQLquery +="@\"";
        SQLquery +=newUserArgs[2];
        SQLquery +="\"";
        qDebug()<<SQLquery;
        //thisMySql[conIndex]->query(SQLquery.toStdString().c_str());
        Query(SQLquery,conIndex);
        SQLquery ="flush privileges";
        Query(SQLquery,conIndex);
    }
}

void Widget::treeViewDropUserSlot()
{
    tableLoseFocus();
    if(ui->treeWidget->currentItem() ==nullptr)
    {
        QMessageBox::warning(this,"Error","Please Select a Connection!");
        return;
    }
    DelUser =new DeleteUser(this);
    DelUser->open();
    connect(DelUser,SIGNAL(accepted()),this,SLOT(rcvDelUserOk()),Qt::AutoConnection);
    connect(DelUser,SIGNAL(rejected()),this,SLOT(rcvDelUserCancel()),Qt::UniqueConnection);
}

void Widget::treeViewPassWdRst()
{
    tableLoseFocus();
    cur =ui->treeWidget->currentItem();
    if (cur ==nullptr)
    {
        QMessageBox::information(this,"Error","Please Select a Connection!");
        return;
    }
    int conIndex;
    if(cur->parent()==nullptr)
        conIndex=ui->treeWidget->indexOfTopLevelItem(cur);
    else if (cur->parent()->parent()==nullptr)
        conIndex=ui->treeWidget->indexOfTopLevelItem(cur->parent());
    else
        conIndex=ui->treeWidget->indexOfTopLevelItem(cur->parent()->parent());
    QString SQLquery ="use mysql";
    Query(SQLquery,conIndex);
    if(thisMySql[conIndex]->lastQueryValid())
    {
        rstPwd =new resetPwd(this);
        //rstPwd->setWindowFlags(Qt::FramelessWindowHint);
        rstPwd->open();
        childrenNums++;
        //rstPwd->setWindowModality(Qt::ApplicationModal);
        //this->setDisabled(true);
        connect(rstPwd,SIGNAL(accepted()),this,SLOT(recvRstPasswdOk()),Qt::AutoConnection);
        connect(rstPwd,SIGNAL(rejected()),this,SLOT(recvRstPasswdClosed()),Qt::AutoConnection);

    }
}

void Widget::recvRstPasswdClosed()
{
    delete rstPwd;
    rstPwd =nullptr;
    if(--childrenNums==0);
}

void Widget::recvRstPasswdOk()
{
    QStringList pwdArgs =rstPwd->getInput();
    recvRstPasswdClosed();
    QString SQLquery ="update user set authentication_string =password(\"";
    SQLquery ==pwdArgs[1];
    SQLquery +="\") where user =\"";
    SQLquery +=pwdArgs[0];
    SQLquery +="\"";
    int conIndex =ui->treeWidget->indexOfTopLevelItem(ui->treeWidget->currentItem());
    Query(SQLquery,conIndex);
}

void Widget::rcvDelUserCancel()
{
    delete DelUser;
    DelUser =nullptr;
}

void Widget::rcvDelUserOk()
{
    QStringList tmp =DelUser->getInput();
    rcvDelUserCancel();
    cur =ui->treeWidget->currentItem();
    int conIndex;
    QString SQLquery;
    if(cur->parent()==nullptr)
        conIndex=ui->treeWidget->indexOfTopLevelItem(cur);
    else if (cur->parent()->parent()==nullptr)
        conIndex=ui->treeWidget->indexOfTopLevelItem(cur->parent());
    else
        conIndex=ui->treeWidget->indexOfTopLevelItem(cur->parent()->parent());
    if(tmp[0] =="drop")
    {
        SQLquery ="drop user ";
        SQLquery +=tmp[1] +"@'";
        SQLquery +=tmp[2]+"'";
        Query(SQLquery,conIndex);
    }
    else
    {
        SQLquery ="use mysql";
        Query(SQLquery,conIndex);
        if(!thisMySql[conIndex]->lastQueryValid())
            return;
        SQLquery ="delete from user where user ='";
        SQLquery +=tmp[1]+"' and host ='";
        SQLquery +=tmp[2]+"'";
        Query(SQLquery,conIndex);
    }
}

void Widget::tableItemChangedSlot(QTableWidgetItem *changedItem)
{

   int ItemRow =changedItem->row(),ItemCol =changedItem->column();
   qDebug()<<ItemRow<<" "<<ItemCol;
   QString SQLquery;
   bool isStr;
   SQLquery ="use ";
   SQLquery +=tableDBName;
   Query(SQLquery,tableConIndex);
   isStr =tableDescribe[ItemCol][1].contains("text",Qt::CaseInsensitive) || tableDescribe[ItemCol][1].contains("char",Qt::CaseInsensitive);
   SQLquery ="update ";
   SQLquery +=ui->tableWidget->windowTitle()
           +" set "+ui->tableWidget->horizontalHeaderItem(ItemCol)->text();

   if(changedItem->text().isEmpty())
       SQLquery +=" = null ";
   else
   {
       SQLquery +=" = ";
   if(isStr)
       SQLquery +="'";
    SQLquery +=changedItem->text();
    if(isStr)
        SQLquery +="'";
   }
    SQLquery += " where ";


   if(ItemCol !=0)
   {
       SQLquery +=ui->tableWidget->horizontalHeaderItem(0)->text();
       isStr =tableDescribe[0][1].contains("text",Qt::CaseInsensitive) || tableDescribe[0][1].contains("char",Qt::CaseInsensitive);
       if(ui->tableWidget->item(ItemRow,0)->text().isEmpty())
           SQLquery +=" is null";
       else
       {
           SQLquery +=" = ";
       if(isStr)
           SQLquery +="'";
       SQLquery +=ui->tableWidget->item(ItemRow,0)->text();
       if(isStr)
           SQLquery +="'";
       }
       for (int i =1;i<ui->tableWidget->columnCount();i++)
       {
           if(i !=ItemCol)
           {
           SQLquery +=" and ";
           SQLquery += ui->tableWidget->horizontalHeaderItem(i)->text();
           isStr =tableDescribe[i][1].contains("text",Qt::CaseInsensitive) || tableDescribe[i][1].contains("char",Qt::CaseInsensitive);
           if(ui->tableWidget->item(ItemRow,i)->text().isEmpty())
               SQLquery +=" is null ";
           else
           {
               SQLquery += " = ";
           if(isStr)
               SQLquery +="'";
            SQLquery +=ui->tableWidget->item(ItemRow,i)->text();
            if(isStr)
                SQLquery +="'";
           }
           }
       }
   }
   else
   {
       SQLquery +=ui->tableWidget->horizontalHeaderItem(1)->text();
       isStr =tableDescribe[1][1].contains("text",Qt::CaseInsensitive) || tableDescribe[1][1].contains("char",Qt::CaseInsensitive);
       if(ui->tableWidget->item(ItemRow,1)->text().isEmpty())
           SQLquery +=" is null ";
       else
       {
           SQLquery +=" = ";
       if(isStr)
           SQLquery +="'";
       SQLquery +=ui->tableWidget->item(ItemRow,1)->text();
       if(isStr)
           SQLquery +="'";
       }
       for (int i =2;i<ui->tableWidget->columnCount();i++)
       {
           SQLquery +=" and ";
           SQLquery += ui->tableWidget->horizontalHeaderItem(i)->text();
           isStr =tableDescribe[i][1].contains("text",Qt::CaseInsensitive) || tableDescribe[i][1].contains("char",Qt::CaseInsensitive);
           if(ui->tableWidget->item(ItemRow,i)->text().isEmpty())
               SQLquery +=" is null";
           else
           {
               SQLquery +=" = ";
           if(isStr)
               SQLquery +="'";
           SQLquery +=ui->tableWidget->item(ItemRow,i)->text();
           if(isStr)
               SQLquery +="'";
           }

       }
   }
   qDebug()<<SQLquery;
   Query(SQLquery,tableConIndex);

}


void Widget::tableItemActivatedSlot()
{
    connect(ui->tableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(tableItemChangedSlot(QTableWidgetItem*)),Qt::AutoConnection);

}


void Widget::tableLoseFocus()
{
    disconnect(ui->tableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(tableItemChangedSlot(QTableWidgetItem*)));
    qDebug()<<"table Lose Focus, Disconnected";
}

void  Widget::newTableSlot()
{
    pNewTable =new NewTable(this);
    pNewTable->open();
    connect(pNewTable,SIGNAL(accepted()),this,SLOT(newTableOkSLot()),Qt::AutoConnection);
    connect(pNewTable,SIGNAL(rejected()),this,SLOT(newTableCancelSlot()),Qt::AutoConnection);
}


void Widget::newTableOkSLot()
{
    qDebug()<<"Start Get Input Table";
    std::vector<QStringList> tableInfo =pNewTable->getInput();
    qDebug()<<"Ended Input";
    if(tableInfo.empty())
    {
        qDebug()<<"Reopen";
        pNewTable->open();
        return;
    }
    newTableCancelSlot();
    QString SQLquery ="create table ";
    SQLquery +=tableInfo.back()[0] +"(";
    for(int i=0;i <tableInfo.size()-1;i ++)
    {
        for(int j =0;j <tableInfo[i].size();j ++)
            SQLquery +=tableInfo[i][j]+" ";
        SQLquery +=",";
    }
    SQLquery.remove(SQLquery.size() -1,1) +=")";
    cur =ui->treeWidget->currentItem();
    int conIndex =ui->treeWidget->indexOfTopLevelItem(cur->parent());
    qDebug()<<SQLquery;

    Query(SQLquery,conIndex);

}

void Widget::newTableCancelSlot()
{
    delete pNewTable;
    pNewTable =nullptr;
}

void Widget::tableNewInsert()
{
    int conIndex;
    QString SQLquery ="use ";
    if(!insertFromTable)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur->parent()->parent());
        SQLquery +=cur->parent()->text(0);
        Query(SQLquery,conIndex);
        SQLquery ="describe ";
        SQLquery +=cur->text(0);
        tableQuery(SQLquery,conIndex);
        if(thisMySql[conIndex]->lastQueryValid())
                treeTableDescribe =*(thisMySql[conIndex]->tableResult);
        qDebug()<<"Lauching NewInsert Dialog";
        pNewInsert =new NewInsert(this,treeTableDescribe);
    }
    else
    {
        conIndex =tableConIndex;
        SQLquery +=tableDBName;
        Query(SQLquery,conIndex);
        qDebug()<<"Lauching NewInsert Dialog";
        pNewInsert =new NewInsert(this,tableDescribe);
    }
    pNewInsert->open();
    connect(pNewInsert,SIGNAL(accepted()),this,SLOT(newInsertOkSlot()),Qt::AutoConnection);
    connect(pNewInsert,SIGNAL(rejected()),this,SLOT(newInsertCacelSlot()),Qt::AutoConnection);

}


void Widget::newInsertCacelSlot()
{
    delete pNewInsert;
    pNewInsert =nullptr;
}

void Widget::newInsertOkSlot()
{
    std::vector<QStringList> input =pNewInsert->getInput();
    newInsertCacelSlot();
    QString SQLquery,tableName;
    int conIndex;
    if(!insertFromTable)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur->parent()->parent());
        tableName =cur->text(0);
    }
    else
    {
        conIndex =tableConIndex;
        tableName =ui->tableWidget->windowTitle();
    }
    for (auto& val:input)
    {
        SQLquery ="insert into ";
        SQLquery +=tableName +"(";
        SQLquery +=val[0] +")" +" values(";
        SQLquery +=val[1] +")";
        Query(SQLquery,conIndex);
    }
    if(insertFromTable)
    {
        SQLquery ="select * from ";
        SQLquery +=ui->tableWidget->windowTitle();
        tableQuery(SQLquery,conIndex);
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(thisMySql[conIndex]->tableResult->size());
        for (int i =0,len =thisMySql[conIndex]->tableResult->size();i<len;i ++)
            for (int j =0,l =thisMySql[conIndex]->tableResult->at(i).size();j <l;j ++)
                ui->tableWidget->setItem(i,j,new QTableWidgetItem((*(thisMySql[conIndex]->tableResult))[i][j]));
    }
}

void Widget::treeViewAlterSlot()
{
    cur =ui->treeWidget->currentItem();
    if(cur ==nullptr||cur->parent() ==nullptr||cur->parent()->parent()==nullptr)
        return;
    pTableAlter =new tableAlter(this);
    pTableAlter->open();
    connect(pTableAlter,SIGNAL(accepted()),this,SLOT(tableAlterOkSlot()),Qt::AutoConnection);
    connect(pTableAlter,SIGNAL(rejected()),this,SLOT(tableAlterCancelSlot()),Qt::AutoConnection);
}

void Widget::tableAlterCancelSlot()
{
    delete pTableAlter;
    pTableAlter =nullptr;

}

void Widget::tableAlterOkSlot()
{
    QString input =pTableAlter->getInput();
    tableAlterCancelSlot();
    if(input.isEmpty())
    {
        QMessageBox::warning(this,"input Error","Empty input");
        return;
    }
    QString SQLquery="use ";
    int conIndex =ui->treeWidget->indexOfTopLevelItem(cur->parent()->parent());
    SQLquery +=cur->parent()->text(0);
    Query(SQLquery,conIndex);
    if(!thisMySql[conIndex]->lastQueryValid())
        return;
    SQLquery ="alter table ";
    SQLquery +=cur->text(0) +" " +input;
    Query(SQLquery,conIndex);

}

void Widget::backupSlot()
{
    cur =ui->treeWidget->currentItem();
    if(cur ==nullptr)
        return;
    QFileDialog saveFile;
    saveFile.setAcceptMode(QFileDialog::AcceptSave);
    saveFile.setFileMode(QFileDialog::AnyFile);
    QString FilePath =QFileDialog::getSaveFileName(this,"SavePath","./","SQL File(*.sql)");
    QString cmdInput ="mysqldump ";
    QString backupType;
    int conIndex;
    if(cur ->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur);
        backupType ="--all-databases";
    }
    else if(cur->parent()->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur->parent());
        backupType =cur->text(0);
    }
    else if(cur->parent()->parent()->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur->parent()->parent());
        backupType =cur->parent()->text(0)+" "+cur->text(0);
    }
    cmdInput +="-h";
    cmdInput +=conInfo[conIndex][1] +" ";
    cmdInput +="-P";
    cmdInput +=conInfo[conIndex][2] +" ";
    cmdInput +="-u";
    cmdInput +=conInfo[conIndex][3] +" ";
    cmdInput +="-p";
    cmdInput +=conInfo[conIndex][4] +" ";
    cmdInput +=backupType;
    QProcess cmd;
    cmd.setStandardOutputFile(FilePath);
    cmd.start(cmdInput);
    if(cmd.waitForFinished())
    {
        QMessageBox::information(this,"BackUp","Backup Succeeded");
    }
    else
    {
        QMessageBox::warning(this,"BackUp","Backup Failed");
    }
}

void Widget::recoverySlot()
{
    cur =ui->treeWidget->currentItem();
    if(cur ==nullptr)
        return;
    QFileDialog saveFile;
    saveFile.setAcceptMode(QFileDialog::AcceptOpen);
    saveFile.setFileMode(QFileDialog::ExistingFiles);
    saveFile.setOption(QFileDialog::ReadOnly,true);
    QString FilePath =QFileDialog::getOpenFileName(this,"OpenFilePath","./","SQL File(*.sql)");
    QString cmdInput ="mysqldump ";
    QString backupType;
    int conIndex;
    if(cur ->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur);
        backupType ="--all-databases";
    }
    else if(cur->parent()->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur->parent());
        backupType =cur->text(0);
    }
    else if(cur->parent()->parent()->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur->parent()->parent());
        backupType =cur->parent()->text(0)+" "+cur->text(0);
    }

    cmdInput +="-h";
    cmdInput +=conInfo[conIndex][1] +" ";
    cmdInput +="-P";
    cmdInput +=conInfo[conIndex][2] +" ";
    cmdInput +="-u";
    cmdInput +=conInfo[conIndex][3] +" ";
    cmdInput +="-p";
    cmdInput +=conInfo[conIndex][4] +" ";
    cmdInput +=backupType;
    QProcess cmd;
    cmd.setStandardInputFile(FilePath);
    cmd.start(cmdInput);
    if(cmd.waitForFinished())
    {
        QMessageBox::information(this,"Reecovery","Recovery Succeeded");
    }
    else
    {
        QMessageBox::warning(this,"Recovery","Recovery Failed");
    }


}



void Widget::on_pushButton_2_clicked()
{
    cur=ui->treeWidget->currentItem();
    if(cur ==nullptr)
        return;
    QString SQlquery =ui->plainTextEdit->toPlainText();
    int conIndex;
    if(cur ->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur);
    }
    else if(cur->parent()->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur->parent());
    }
    else if(cur->parent()->parent()->parent() ==nullptr)
    {
        conIndex =ui->treeWidget->indexOfTopLevelItem(cur->parent()->parent());
    }
    Query(SQlquery,conIndex);
}
