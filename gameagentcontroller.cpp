#include "gameagentcontroller.h"

#include <QJsonDocument>

GameAgentController::GameAgentController(QObject *parent)
    : QObject{parent}
{}

void GameAgentController::init()
{
    _config.model = "llama3.2";

    // Construct a response format json schema for the game command:
    QJsonObject format;
    format["type"] = "object";
    QJsonObject properties;
    properties["cmd"] = QJsonObject {{"type", "string"}};
    properties["learnedSoFar"] = QJsonObject {{"type", "string"}};
    format["properties"] = properties;
    _config.format = format;
    _config.system = _createPrompt();

    QObject::connect(&_client, &ApiClient::responseReceived,
                     [&](const QString &response) {
                         _parseAiResponse(response);
    });

    qDebug() << "Initialization Complte.";
    qDebug() << "Model: " << _config.model;
    qDebug() << "System Prompt: " << _config.system;
}

void GameAgentController::runGame()
{
    QString nextPrompt = _interface.createGameStateJson();
    _client.generate(_config, nextPrompt);
}

QString GameAgentController::_createPrompt()
{
    QString goal = _createGoalPrompt();
    QString prompt = "You are an AI Agent named Falken.\n"
                     "You are playing a Tamagatchi style game where you have "
                     "a virtual goblin who has various needs.\n"
                     "This is a turn based game: You will receive information "
                     "about the game state and deliver commands on each of your "
                     "turns./n"
                     "Your goal is to " + goal + ". The User is a Game Agent "
                     "Program, that will send you JSON containing information "
                     "about the game's state. You must use this information "
                     "to play the game in a way that achieves your goal with "
                     "this game.\n"
                     "Your responses will also be JSON, in the following "
                     "format: `{ \"cmd\": \"your command\", \"learnedSoFar\": "
                     "\"What you've learned about how to best achieve your "
                     "goals by playing this game.\" }`.\n"
                     "The commands available to you are: sleep, eat, play, "
                     "pee, talk, shower, clean, wait.\n"
                     "If you attempt any unrecognized commands, you will get "
                     "back an error JSON and your turn will not be taken "
                     "until you submit a valid command in the correct JSON "
                     "format.\n"
                     "The `learnedSoFar` JSON is for you to submit any "
                     "musings you have about what you've learned about "
                     "playing this game so far.\n"
                     "You can submit any text in `learnedSoFar` as it will "
                     "not be parsed (only logged by the game).\n"
                     "Here you can talk about observations about how the game "
                     "works, what you think you should be doing, what you "
                     "think doesn't work, or anything at all.\n"
                     "Its purpose is to help you strategise to meet your goals.";
    return prompt;
}

QString GameAgentController::_createGoalPrompt()
{
    return "make sure the goblin survives 10 turns";
}

void GameAgentController::_parseAiResponse(const QString &response)
{
    // Parse the response:
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    QString responseStr = jsonObj["response"].toString();

    if (responseStr.isEmpty()) {
        qWarning() << "Invalid response from AI: " << response;
    }

    // Process the game JSON:
    _interface.parseGameCommand(responseStr);

    // Send the Game State JSON Back:
    QString nextPrompt = _interface.createGameStateJson();
    _client.generate(_config, nextPrompt);
}
