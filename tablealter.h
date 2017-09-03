#ifndef TABLEALTER_H
#define TABLEALTER_H

#include <QDialog>

namespace Ui {
class tableAlter;
}

class tableAlter : public QDialog
{
    Q_OBJECT

public:
    explicit tableAlter(QWidget *parent = 0);
    ~tableAlter();
   QString getInput();
private:
    Ui::tableAlter *ui;
    //void resetInputRemind();
private slots:
    void OpChangedSlot(QString);
    void TypeChangedSlot(QString);
};

#endif // TABLEALTER_H
