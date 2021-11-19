#ifndef FENETRE_H
#define FENETRE_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QtGui>
#include <QMessageBox>
#include <QMqttClient>

///@file fenetre.h
#include "pixelix.h"

QT_BEGIN_NAMESPACE
namespace Ui { class fenetre; }
QT_END_NAMESPACE

class fenetre : public QMainWindow
{
    Q_OBJECT

public:
    fenetre(QWidget *parent = nullptr);
    ~fenetre();
    QColor couleur = Qt::white;

private slots:
    void telecharger_brightness();
    void envoyer_txt();
    void choixcouleur();
    void changer_url();
    void envoyer_lum();
//    void reponse_terminee(QNetworkReply *reply);
    void on_send_brightness_sliderMoved(int value);

private:
    Ui::fenetre *ui;
    bool erreurTrouvee = false;
    pixelix afficheur;
    QMqttClient *m_client;
//    QByteArray answer;
//    QNetworkAccessManager *m;
//    QNetworkRequest requete;
//    bool getfini = false;


};
#endif // FENETRE_H
