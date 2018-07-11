#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "QMouseEvent"
#include <QDialog>

namespace Ui {
class logindialog;
}

class logindialog : public QDialog
{
    Q_OBJECT

public:
    explicit logindialog(QWidget *parent = 0);
    ~logindialog();

private slots:
    void on_pushButton_clicked();
    void login(QString);
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
  //  void on_lineEdit_textEdited(const QString &arg1);
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    Ui::logindialog *ui;
    QPoint last;
};

#endif // LOGINDIALOG_H
