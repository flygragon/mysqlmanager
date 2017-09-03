#ifndef RESETPWD_H
#define RESETPWD_H

#include <QDialog>

namespace Ui {
class resetPwd;
}

class resetPwd : public QDialog
{
    Q_OBJECT

public:
    explicit resetPwd(QWidget *parent = 0);
    ~resetPwd();
    QStringList getInput();

private:
    Ui::resetPwd *ui;
};

#endif // RESETPWD_H
