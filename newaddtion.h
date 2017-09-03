#ifndef NEWADDTION_H
#define NEWADDTION_H

#include <QWidget>

namespace Ui {
class newAddtion;
}

class newAddtion : public QWidget
{
    Q_OBJECT

public:
    explicit newAddtion(QWidget *parent = 0);
    ~newAddtion();
    void setUiLabelText(QString&);
   public slots:
    void okClicked();
    void cancelClicked();

private:
    Ui::newAddtion *ui;
signals:
    void okSignal(QString&);
    void cancelSignal();
};

#endif // NEWADDTION_H
