#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class registerDialog;
}

class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget *parent = 0);
    ~registerDialog();

private slots:
    void on_pushButton_clicked();
    void signup(QString);

private:
    Ui::registerDialog *ui;
};

#endif // REGISTERDIALOG_H
