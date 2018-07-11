#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPixmap>
#include<QStyledItemDelegate>
#include<QObject>
#include<QPainter>
#include<QLabel>
#include<QHeaderView>
#include<QTableWidget>
#include<QTableWidgetItem>
#include "phototool.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void afterLogin();

public slots:
    void openDialog(QTableWidgetItem *item);
    void configWidget(vector<vector<vector<Image>>>);

private slots:
    void on_upbtn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


private:
    Ui::MainWindow *ui;
    vector<vector<vector<Image> > > vec;
    int classifyType;
    QString path;
};

class QPixmapItemdele : public QStyledItemDelegate
{
public:
    QPixmapItemdele(QObject* parent = 0):QStyledItemDelegate(parent){ }


    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
       {
           if(index.data(Qt::DisplayRole).canConvert<QPixmap>())
           {
               QPixmap pix = index.data(Qt::DisplayRole).value<QPixmap>();
               painter->drawPixmap(option.rect,pix);
           }

           QStyledItemDelegate::paint(painter,option,index);
       }

   };

#endif // MAINWINDOW_H
