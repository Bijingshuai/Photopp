#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include "phototool.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    logindialog dlg;
   if(dlg.exec()==QDialog::Accepted) {

//        w.show();
        w.afterLogin();
   }


    return a.exec();
}
