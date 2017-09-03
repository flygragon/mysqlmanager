#ifndef ADDITIONNEW_H
#define ADDITIONNEW_H

#include <QDialog>

namespace Ui {
class AdditionNew;
}

class AdditionNew : public QDialog
{
    Q_OBJECT

public:
    explicit AdditionNew(QWidget *parent = 0);
    ~AdditionNew();
    void setUiLabelText(QString&);
    QString getInput();

private:
    Ui::AdditionNew *ui;
};

#endif // ADDITIONNEW_H
