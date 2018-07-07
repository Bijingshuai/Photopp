#ifndef USERTOOL_H
#define USERTOOL_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QString>

class UserTool : public QObject
{
    Q_OBJECT

public:
    explicit UserTool();
    ~UserTool();

    void checkconnection(/*QString,QString*/);
    void login(QString,QString);
    void signup(QString,QString);
    bool loginhistory();


private:
    QNetworkAccessManager *signmanager;
    QString jwt;

signals:
    void getserverdata(QString fromserver);


public slots:
//    void finished();
    void finishedslot(QNetworkReply*reply);
};

#endif // USERTOOL_H
