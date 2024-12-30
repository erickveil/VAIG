#ifndef SIMGOBLIN_H
#define SIMGOBLIN_H

#include <QString>

class SimGoblin
{
public:

    int rest = 10;
    int hunger = 10;
    int fun = 10;
    int bladder = 10;
    int social = 10;
    int hygene = 10;
    int environment = 10;

    QString status = "happy";
    QString currentActivity = "idle";

    SimGoblin();

    void endTurn();

    void sleep();
    void eat();
    void play();
    void pee();
    void talk();
    void shower();
    void clean();
    void wait();


};


#endif // SIMGOBLIN_H
