#ifndef SIMGOBLIN_H
#define SIMGOBLIN_H

#include <QString>

class SimGoblin
{
public:

    int rest = 10;
    int satiety = 10;
    int fun = 10;
    int bladder = 0;
    int social = 10;
    int hygene = 10;
    int environment = 10;

    QString status = "happy";
    QString currentActivity = "idle";

    SimGoblin();

    QString command(QString cmd);

    void endTurn();

    void sleep();
    void eat();
    void play();
    void pee();
    void talk();
    void shower();
    void clean();
    void wait();

    bool isDead();


};


#endif // SIMGOBLIN_H
