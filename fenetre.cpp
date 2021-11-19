///@file fenetre.cpp
#include "fenetre.h"
#include "ui_fenetre.h"
#include "pixelix.h"

#include <QColorDialog>
#include <QColor>
fenetre::fenetre(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::fenetre)
{
    ui->setupUi(this);
    m_client = new QMqttClient(this);
    m_client->setHostname("172.21.28.19");
    m_client->setPort(1883);

    afficheur.set_url(ui->urlEdit->text());
}
/**
 * @brief Destructeur pour la fenêtre et pour m_client
 */
fenetre::~fenetre()
{
    delete ui;
    delete m_client;
}

/**
 * @brief Récupère le fichier JSON et en extrait la luminosité de l'afficheur
 */
void fenetre::telecharger_brightness()
{
    ui->telechargementButton->setEnabled(false);

    QJsonDocument documentJSON = QJsonDocument::fromJson(afficheur.get_json_brightness());
    qDebug() << documentJSON;
    double brightness = afficheur.get_brightness();
    ui->brightnessprogressBar->setValue(double(brightness/2.55));
    ui->textBrowser->setText(documentJSON.toJson());

    ui->telechargementButton->setEnabled(true);

}
/**
 * @brief Récupère la valeur du slider luminosité et le transforme en integer
 */
void fenetre::envoyer_lum()
{
    QString valeur = ui->label_2->text();
    int value = valeur.toInt();
    afficheur.set_url(ui->urlEdit->text());
    afficheur.brightness(value);
    afficheur.envoyer_lum();
}
/**
 * @brief Récupère le document JSON de la fonction text dans pixelix.cpp puis l'envoie à l'afficheur via MQTT
 */
void fenetre::envoyer_txt()
{
//    afficheur.set_url(ui->urlEdit->text());
//    afficheur.text(ui->send_txt->text(),couleur,ui->ScrollButton->isChecked());
//    afficheur.envoyer_txt();
//    ui->telechargementButton->setEnabled(true);

    QString topic = "lafayette/212/PixelIt/setScreen";
    QByteArray message = afficheur.text(ui->send_txt->text(),couleur,ui->ScrollButton->isChecked());
    qDebug() << message;
    m_client->connectToHost();
    m_client->publish(topic , message);
    m_client->disconnect();
}

/**
 * @brief Modifie la couleur du texte de l'afficheur
 */
void fenetre::choixcouleur()
{
    couleur = QColorDialog::getColor(Qt::white,this,"Couleur du texte");
    if (couleur.isValid()){
        QString qss = QString("background-color: %1").arg(couleur.name());
        ui->couleurButton->setStyleSheet(qss);
    }
}

/**
 * @brief Modifie l'URL affichée dans la barre de texte
 */
void fenetre::changer_url()
{
    afficheur.set_url(ui->urlEdit->text());
}
/**
 * @brief Récupère la valeur du slider et l'envoie au label adjacent
 * @param value
 */
void fenetre::on_send_brightness_sliderMoved(int value)
{
    QString bright =QString::number(value);
    ui->label_2->setText(bright);
}
