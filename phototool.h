#ifndef PHOTOTOOL_H
#define PHOTOTOOL_H

#include "usertool.h"//添加以使用jwt

#include <QObject>
#include <QNetworkAccessManager>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QBuffer>
#include <QImage>
#include <QPixmap>
#include <QByteArray>
#include <sstream>
#include <QVector>
#include <vector>

using namespace std;

typedef struct {
    QString id;
    QString location;
    bool face;

} Image;

class PhotoTool : public QObject
{
    Q_OBJECT

public:
    explicit PhotoTool();
    ~PhotoTool();


    void uploadPhoto(QString);
    void confirmId();
    QString readexif(QString);
    //void getCommonVector();
    //void getLocationVector();
    //void getFaceVector();

public slots:
    void uploadFinished(QNetworkReply*);
    void downloadPhoto(QNetworkReply*);

    void classification(QNetworkReply *);

private:

    QNetworkAccessManager *updownManager;
    QNetworkAccessManager *classifyManager;
    QString jwtString;
    QString path;
    vector<vector<Image>> commmonVec;
    vector<vector<Image>> locationVec;
    vector<vector<Image>> faceVec;
};


#endif // PHOTOTOOL_H
