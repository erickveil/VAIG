#include <QCoreApplication>

#include "gameagentcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GameAgentController controller;
    controller.init();
    controller.runGame();

    return a.exec();
}
