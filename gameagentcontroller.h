#ifndef GAMEAGENTCONTROLLER_H
#define GAMEAGENTCONTROLLER_H

#include "apiclient.h"
#include "apiConfig.h"
#include "gameinterface.h"

#include <QObject>

class GameAgentController : public QObject
{
    Q_OBJECT

    GameInterface _interface;
    ApiConfig _config;
    ApiClient _client;

public:
    explicit GameAgentController(QObject *parent = nullptr);

    void init();
    void runGame();

signals:

private:
    QString _createPrompt();
    QString _createGoalPrompt();
    void _parseAiResponse(const QString &response);
};

#endif // GAMEAGENTCONTROLLER_H
