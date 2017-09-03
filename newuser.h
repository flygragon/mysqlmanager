#ifndef NEWUSER_H
#define NEWUSER_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QMessageBox>

namespace Ui {
class newUser;
}

class newUser : public QWidget
{
    Q_OBJECT

public:
    explicit newUser(QWidget *parent = 0);
    ~newUser();

private:
    Ui::newUser *ui;
    QStringList getInput();
    void closeEvent(QCloseEvent *event);
private slots:
    void okClicked();
    void cancelClicked();
signals:
    void okSignal(QStringList);
    void closed();
    //void cancelClicked();
};

#endif // NEWUSER_H
