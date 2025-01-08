#include "gameinterface.h"

#include <QJsonDocument>
#include <QJsonObject>

GameInterface::GameInterface()
{

}

void GameInterface::parseGameCommand(QByteArray cmdJson)
{
    QJsonDocument doc = QJsonDocument::fromJson(cmdJson);
    if (doc.isNull()) {
        isError = true;
        lastError = "Invalid JSON received from player agent.";
        return;
    }
    QJsonObject obj = doc.object();
    if (!obj.contains("cmd")) {
        isError = true;
        lastError = "Missing 'cmd' field in JSON.";
        return;
    }
    QString cmd = obj["cmd"].toString();
    QString result = _goblin.command(cmd);
    if (!result.isEmpty()) {
        isError = true;
        lastError = result;
        return;
    }
    ++turns;
    _goblin.endTurn();

    qDebug() << "Player Agent: " << cmdJson;
}

QString GameInterface::createGameStateJson()
{
    if (isError) {
        QJsonObject obj;
        obj["error"] = lastError;
        QString result = QJsonDocument(obj).toJson();
        qDebug() << "Game Agent: " << result;
        return result;
    }

    QJsonObject obj;
    obj["rest"] = _goblin.rest;
    obj["hunger"] = _goblin.hunger;
    obj["fun"] = _goblin.fun;
    obj["bladder"] = _goblin.bladder;
    obj["social"] = _goblin.social;
    obj["hygene"] = _goblin.hygene;
    obj["environment"] = _goblin.environment;
    obj["status"] = _goblin.status;
    obj["currentActivity"] = _goblin.currentActivity;
    obj["turns"] = turns;
    QString result = QJsonDocument(obj).toJson();
    qDebug() << "Game Agent: " << result;
    return result;

}
