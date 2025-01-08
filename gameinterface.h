#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "simgoblin.h"


/**
 * @brief The GameInterface class
 * Handles the JSON game command input, and the game state output as JSON.
 * Tracks game turns and win conditions.
 */
class GameInterface
{

    SimGoblin _goblin;
    int turns = 0;

public:
    enum GameGoal {
        None,
        SurviveTenTurns
    };

    GameGoal goal = SurviveTenTurns;

    bool isError = false;
    QString lastError = "";

    GameInterface();

    /**
     * @brief parseGameCommand
     * AI should generate JSON like this:
     *
     * ```json
     * {
     *   "cmd": "sleep",
     *   "learnedSoFar": "Sleeping improves the rest score."
     * }
     * ```
     *
     * This will parse the cmd value and execute the comand, advance the turn
     * counter by one point, call the endTurn method, and log the command that
     * was given to stdout.
     *
     * If something goes wrong (cmdJson is incorrect input somehow), this
     * will generate an error by setting the error bool to true, and setting
     * the lastError string.
     *
     * @param cmdJson
     */
    void parseGameCommand(QByteArray cmdJson);

    /**
     * @brief createGameStateJson
     *
     * This will generate a JSON string with the current game state.
     *
     * ```json
     * {
     *     "rest": 10,
     *     "hunger": 10,
     *     "fun": 10,
     *     "bladder": 10,
     *     "social": 10,
     *     "hygene": 10,
     *     "environment": 10,
     *     "status": "happy",
     *     "currentActivity": "idle",
     *     "turns": 0
     * }
     * ```
     *
     * If isError is true, it will set to false, and then generate this json:
     *
     * ```json
     * {
     *    "error": "Some error message"
     * }
     * ```
     *
     * It will also log this message to stdout after generating it.
     *
     * @return
     */
    QString createGameStateJson();

private:
    void _checkWinCondition();
};

#endif // GAMEINTERFACE_H
