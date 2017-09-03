#ifndef SETBACKUPPATH_H
#define SETBACKUPPATH_H

#include <QDialog>

namespace Ui {
class setBackupPath;
}

class setBackupPath : public QDialog
{
    Q_OBJECT

public:
    explicit setBackupPath(QWidget *parent = 0);
    ~setBackupPath();

private:
    Ui::setBackupPath *ui;
private slots:
    void getFileDialogPath();
};

#endif // SETBACKUPPATH_H
