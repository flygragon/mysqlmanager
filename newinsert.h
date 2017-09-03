#ifndef NEWINSERT_H
#define NEWINSERT_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class NewInsert;
}

class NewInsert : public QDialog
{
    Q_OBJECT

public:
    explicit NewInsert(QWidget *parent);
    explicit NewInsert(QWidget *parent ,std::vector<std::vector<QString>>&);
    ~NewInsert();
    std::vector<QStringList> getInput();

private:
    Ui::NewInsert *ui;
    std::vector<std::vector<QString>> tableDescribe;
private slots:
    void addTableItem();
    void delTableItem();
};

#endif // NEWINSERT_H
