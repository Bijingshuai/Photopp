#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H
#include "QMouseEvent"
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

    //void on_pushButton_2_clicked();
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    Ui::registerDialog *ui;
    QPoint last;
};

#endif // REGISTERDIALOG_H
