///@file pixelit.cpp
#include "pixelix.h"
#include "fenetre.h"
pixelix::pixelix()
{

}
/**
 * @brief
 * Crée un document JSON et le retourne sous forme de QByteArray
 * @param text
 * @param color
 * @param scroll
 * @return message
 */
QByteArray pixelix::text(QString text, QColor color, bool scroll)
{

    // Creation de json text pour Pixelit
    QJsonObject jtext;
    QJsonObject jcolor;
    QJsonObject jposition;

    jtext["textString"] = text;
    jtext["bigFont"] = true;
    jtext["scrollText"] = scroll;
    jtext["scrollTextDelay"] = 100;
    jtext["centerText"] = false;
    jposition["x"] = 8;
    jposition["y"] = 0;
    jtext["position"] = jposition;
    jtext["hexColor"] = color.name();
    jsontext["text"] = jtext;
    QJsonDocument jsondoc(jsontext);
    QByteArray message = jsondoc.toJson();
    return message;
}
/**
 * @brief Crée un objet JSON contenant la valeur souhaitée de la luminosité
 * @param lum
 */
void pixelix::brightness(int lum)
{
    QJsonObject jtext;
    int lume = (lum*2.55);
    jsonlum["brightness"] =  lume;

    qDebug() << jsontext;
}
/**
 * @brief Récupère l'objet JSON contenant la valeur de la luminosité et l'envoie à l'afficheur
 * @return true si l'envoi a réussi; false si il a échoué
 */
bool pixelix::envoyer_lum()
{
    QUrl url = qurl;
    url.setPath("/api/screen");
    qDebug() << jsonlum;
    QByteArray p = post(url, jsonlum);
    qDebug() << p;
    QString good_response = "OK";
    if (p.contains(good_response.toUtf8())){
        return true;
    }
    else {
        return false;
    }
}
/**
 * @brief Change l'URL à laquelle sont envoyées les requêtes ou les objets JSON
 * @param url
 */
void pixelix::set_url(QString url)
{
    qurl = QUrl(url);
}
/**
 * @brief Envoie le document JSON à l'afficheur via l'API
 * @return true si l'envoi a réussi; false si il a échoué
 */
bool pixelix::envoyer_txt()
{
    QUrl url = qurl;
    url.setPath("/api/screen");
    qDebug() << jsontext;
    QByteArray p = post(url, jsontext);
    qDebug() << p;

    QString good_response = "OK";
    if (p.contains(good_response.toUtf8())){
        return true;
    }
    else {
        return false;
    }

}
/**
 * @brief Télécharge le fichier JSON de l'afficheur et en extrait l'objet luminosité et sa valeur
 * @return L'objet JSON contenant la luminosité ou 0 si celui ci est introuvable.
 */
double pixelix::get_brightness()
{
    QUrl url = qurl;
    url.setPath("/api/brightness");

    //la reponse de l'api est stockée dans un json
    QJsonDocument documentJSON = QJsonDocument::fromJson(get(url));

    //on transforme le json en objet json
    QJsonObject objetJSON = documentJSON.object();

    QStringList listeCles;
    listeCles = objetJSON.keys(); // liste des clés json

    // La valeur json de la clé n°1 est brightness (normalement sinon on retourne 0)

    if(objetJSON[listeCles.at(1)].isDouble())
    {

       return objetJSON[listeCles.at(1)].toDouble();
    }
    else
    {
        return 0;
    }

}
/**
 *pixelix::get
 *@brief Effectue une requête HTML pour télécharger le document JSON de l'afficheur
 *
 */
QByteArray pixelix::get(QUrl url)
{

    QNetworkRequest requete(url);
    QNetworkReply *reply = m.get(requete);

    while (!reply->isFinished())
    {
        qApp->processEvents();
    }

    QByteArray read = reply->readAll();
    reply->close();
    reply->deleteLater();

    return read;

}
/**
 * @brief Effectue une requête HTML pour envoyer le document JSON à l'afficheur
 * @param url
 * @param json
 * @return Réponse de l'API
 */
QByteArray pixelix::post(QUrl url, QJsonObject json)
{
    QNetworkRequest requete(url);
    requete.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m.post(requete, QJsonDocument(json).toJson());
    while (!reply->isFinished())
    {
        qApp->processEvents();
    }
    QByteArray read = reply->readAll();
    reply->close();
    reply->deleteLater();
    return read;
}

/**
 * @brief Récupère l'URL de l'API permettant de télécharger l'objet JSON contenant la valeur de la luminosité de l'afficheur
 * @return L'URL de destination de l'objet JSON
 */
QByteArray pixelix::get_json_brightness()
{
    QUrl url = qurl;
    url.setPath("/api/brightness");
    return get(url);
}
