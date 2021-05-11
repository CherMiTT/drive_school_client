/*!
* \file
* \brief Header file for requests for and to server
* \author CherMiTT
* \date	07.04.2021
* \version 1.0
*/


#ifndef REQUESTER_H
#define REQUESTER_H

#include <QObject>
#include <QString>
#include <QSslConfiguration>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QVariantMap>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

/*!
 * \brief class that handles all requests to and from server
 */
class Requester : public QObject
{
    Q_OBJECT
public:

    /*!
     * \brief The Type enum defines type of http and https request
     */
    enum class Type {
        POST,
        GET,
        PATCH,
        DELETE
    };

    explicit Requester(QObject* parent = nullptr);

    void initRequester(const QString& host, int port, QSslConfiguration* value);
    void sendRequest(const QString& apiStr, Type type = Type::GET, const QByteArray& data = QByteArray()) const;

signals:

private:

    static const QString httpTemplate;
    static const QString httpsTemplate;

    QString host;
    int port;
    QString token; //TODO: add tokenization
    QSslConfiguration* sslConfig;

    QString pathTemplate;

    QNetworkAccessManager* manager;

    [[nodiscard]] QNetworkRequest createRequest(const QString& apiStr) const;
    [[nodiscard]] QByteArray variantMapToJson(QVariantMap data);

private slots:
    bool onFinishRequest(QNetworkReply* reply);

};

#endif // REQUESTER_H
