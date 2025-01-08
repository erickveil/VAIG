#ifndef APICONFIG_H
#define APICONFIG_H

#include <QString>
#include <QJsonObject>

struct ApiConfig {

    QString ip = "http://192.168.0.144:11434";
    QString endpoint = "/api/generate";
    QString model = "llama3.2";
    bool stream = false;
    QString system = "";
    QString key = "";
    bool useContext = true;
    QJsonObject format;
};

#endif // APICONFIG_H
