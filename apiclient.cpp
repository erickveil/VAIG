#include "apiclient.h"

#include <QJsonDocument>
#include <QJsonObject>

ApiClient::ApiClient(QObject *parent) : QObject{parent}
{
    connect(&_networkManager, &QNetworkAccessManager::finished,
            this, &ApiClient::onReplyFinished);
}

void ApiClient::generate(const QString &model, const QString &prompt, bool stream)
{
    ApiConfig config;
    config.model = model;
    config.stream = stream;

    generate(config, prompt);
}

void ApiClient::generate(const ApiConfig &config, QString prompt)
{
    QString urlStr = config.ip + config.endpoint;

    QUrl url(urlStr);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if (config.key != "") {
        request.setRawHeader("Authorization", "Bearer " + config.key.toUtf8());
    }


    QJsonObject json;
    json["model"] = config.model;
    json["prompt"] = prompt;
    json["stream"] = config.stream;

    if (config.system != "") {
        json["system"] = config.system;
    }

    if (config.useContext) {
        json["context"] = _conversationModel.tokenContext;
    }

    if (!config.format.isEmpty()) {
        json["response_format"] = config.format;
    }

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    //qDebug() << "Delivering API request to " << urlStr;
    //qDebug() << jsonData;

    _networkManager.post(request, jsonData);
}

void ApiClient::onReplyFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QString responseString = QString::fromUtf8(responseData);
        _saveTokenContext(responseString);
        emit responseReceived(responseString);
        return;
    }
    else {
        emit responseReceived("API Response Error: " + reply->errorString());
    }
    reply->deleteLater();
}

void ApiClient::_saveTokenContext(const QString &response)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray tokenContext = jsonObj["context"].toArray();
    _conversationModel.tokenContext = tokenContext;
}
