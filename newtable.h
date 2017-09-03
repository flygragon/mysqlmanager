#ifndef NEWTABLE_H
#define NEWTABLE_H

#include <QDialog>
#include <vector>
#include <QMessageBox>

namespace Ui {
class NewTable;
}

class NewTable : public QDialog
{
    Q_OBJECT

public:
    explicit NewTable(QWidget *parent = 0);
    ~NewTable();
    std::vector<QStringList> getInput();

private:
    Ui::NewTable *ui;
private slots:
    void addColumn();
    void delColumn();
};

#endif // NEWTABLE_H
