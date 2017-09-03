#ifndef NEWCONNECTION_H
#define NEWCONNECTION_H

#include <QDialog>
#include <QString>

namespace Ui {
class newConnection;
}

class newConnection : public QDialog
{
    Q_OBJECT

public:
    explicit newConnection(QWidget *parent = 0);
    ~newConnection();
    std::vector<QString>& getConInfo();

private:
    Ui::newConnection *ui;
    std::vector<QString> conInfo;

};

#endif // NEWCONNECTION_H
