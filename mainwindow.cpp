#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include<dialog.h>
#include<QMessageBox>
#include<QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QApplication::setStyle("windows");
    ui->tableWidget->setItemDelegate(new QPixmapItemdele());


   for(int i=0; i<ui->tableWidget->columnCount(); i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem();
            ui->tableWidget->setItem(0,i,item);


            item->setData(Qt::DisplayRole,QVariant::fromValue<QPixmap>(QPixmap(":/new/prefix1/a.png").scaled(60,60)));

        }


    ui->tableWidget->setItemDelegate(new QPixmapItemdele());

        int rowcount=20;
        int colcount=4;

        ui->tableWidget->setColumnCount(colcount);
        ui->tableWidget->setRowCount(rowcount);
        ui->tableWidget->horizontalHeader()->setVisible(false);
        ui->tableWidget->verticalHeader()->setVisible(false);
        ui->tableWidget->setSelectionMode(ui->tableWidget->NoSelection);
        ui->tableWidget->setEditTriggers(ui->tableWidget->SelectedClicked);
        ui->tableWidget->setShowGrid(true);
        ui->tableWidget->setFrameShape(QFrame::NoFrame);

        int width= 600;


        for(int i=0; i<ui->tableWidget->columnCount(); i++)
        {

        ui->tableWidget->setColumnWidth(i,width);
        for(int i=0;i<50;++i)
           {
            QTableWidgetItem *itemi = new QTableWidgetItem();
            ui->tableWidget->setItem(0,i,itemi);
            itemi->setData(Qt::DisplayRole,QVariant::fromValue<QPixmap>(QPixmap(":/new/prefix1/a.png").scaled(60,60)));
            }


            ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

         }

     connect(ui->tableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(openDialog(QTableWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDialog(QTableWidgetItem*)
{
    Dialog dlg1;
    dlg1.resize(400,400);
    dlg1.exec();
}



void MainWindow::on_upbtn_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image Files(*.jpg * .png)"));
    if(path.length()==0)
    {
        QMessageBox::information(NULL,tr("Path"),tr("You didn't select any files."));
    }
    else
    {
        QMessageBox::information(NULL,tr("Path"),tr("You selected")+path);

    }
}
