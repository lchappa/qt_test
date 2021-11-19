#ifndef PIXELIX_H
#define PIXELIX_H

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
///@file pixelix.h
#include <QUrl>
#include <QtGui>
#include <QMessageBox>

class pixelix
{

private:
    QUrl qurl;
    QJsonObject jsontext;
    QJsonObject jsonlum;
    QByteArray get(QUrl url);
    QByteArray post(QUrl url, QJsonObject json);
    QNetworkAccessManager m;


public:
    pixelix();
    QByteArray text(QString text, QColor color, bool scroll);
    void set_url(QString url);
    bool envoyer_txt();
    QByteArray get_json_brightness();
    double get_brightness();
    void brightness(int lum);
    bool envoyer_lum();

};

#endif // PIXELIX_H
