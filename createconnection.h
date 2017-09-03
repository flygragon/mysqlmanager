#ifndef CREATECONNECTION_H
#define CREATECONNECTION_H

#include <QWidget>
#include<QString>

namespace Ui {
class createConnection;
}

class createConnection : public QWidget
{
    Q_OBJECT

public:
    Ui::createConnection *ui;
    explicit createConnection(QWidget *parent = 0);
    ~createConnection();
    std::vector<QString>& getConInfo();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void inputComplete();
    void cancel();

private:
    std::vector<QString> conInfo;
};

#endif // CREATECONNECTION_H
