#ifndef MODIFYPASSWD_H
#define MODIFYPASSWD_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QMessageBox>


namespace Ui {
class modifyPasswd;
}

class modifyPasswd : public QWidget
{
    Q_OBJECT

public:
    explicit modifyPasswd(QWidget *parent = 0);
    ~modifyPasswd();

private:
    Ui::modifyPasswd *ui;
    void closeEvent(QCloseEvent *event);
private slots:
    void okClicked();
    void cancelClicked();
signals:
    void okSignal(QStringList);
    void closed();
};

#endif // MODIFYPASSWD_H
