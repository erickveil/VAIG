#ifndef APICLIENT_H
#define APICLIENT_H

#include <QJsonArray>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "apiConfig.h"
#include "conversationmodel.h"

class ApiClient : public QObject
{
    Q_OBJECT

    QNetworkAccessManager _networkManager;
    ConversationModel _conversationModel;

public:
    explicit ApiClient(QObject *parent = nullptr);
    void generate(const QString &model, const QString &prompt, bool stream);
    void generate(const ApiConfig &config, QString prompt);

signals:
    void responseReceived(const QString &response);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    void _saveTokenContext(const QString &response);

};

#endif // APICLIENT_H
