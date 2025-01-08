#include "simgoblin.h"

SimGoblin::SimGoblin() {}

QString SimGoblin::command(QString cmd)
{
    if (cmd.toLower() == "sleep") {
        sleep();
    }
    else if (cmd.toLower() == "eat") {
        eat();
    }
    else if (cmd.toLower() == "play") {
        play();
    }
    else if (cmd.toLower() == "pee") {
        pee();
    }
    else if (cmd.toLower() == "talk") {
        talk();
    }
    else if (cmd.toLower() == "shower") {
        shower();
    }
    else if (cmd.toLower() == "clean") {
        clean();
    }
    else if (cmd.toLower() == "wait") {
        wait();
    }
    else {
        return "Unknown Command: " + cmd;
    }
    return "";
}

void SimGoblin::endTurn()
{
    --rest;
    if (rest <= 3) {
        status = "tired";
    }
    if (rest <= 0) {
        rest = 0;
        status = "asleep";
    }
    if (rest >= 10) {
        rest = 10;
    }
    --satiety;
    if (satiety <= 3) {
        status = "hungry";
    }
    if (satiety <= 0) {
        satiety = 0;
    }
    if (satiety >= 10) {
        satiety = 10;
    }
    --fun;
    if (fun <= 3) {
        status = "bored";
    }
    if (fun <= 0) {
        fun = 0;
    }
    if (fun >= 10) {
        fun = 10;
    }
    ++bladder;
    if (bladder >= 8) {
        status = "uncomfortable";
    }
    if (bladder <= 0) {
        bladder = 0;
    }
    if (bladder >= 10) {
        bladder = 0;
        hygene -= 5;
        environment -= 5;
        status = "soiled";
    }
    --social;
    if (social <= 3) {
        status = "lonely";
    }
    if (social <= 0) {
        social = 0;
    }
    if (social >= 10) {
        social = 10;
    }
    --hygene;
    if (hygene <= 3) {
        status = "smelly";
    }
    if (hygene <= 0) {
        hygene = 0;
    }
    if (hygene >= 10) {
        hygene = 10;
    }
    --environment;
    if (environment <= 3) {
        status = "unhappy";
    }
    if (environment <= 0) {
        environment = 0;
    }
    if (environment >= 10) {
        environment = 10;
    }

    if (rest <= 2 || satiety <= 2 || fun <= 2 || bladder >= 9 ||
        social <= 2 || hygene <= 2 || environment <= 2) {
        status = "unhappy";
    }
    else if (rest <= 0 || satiety <= 0 ) {
        status = "dead";
    }
    else {
        status = "happy";
    }

}

void SimGoblin::sleep()
{
    rest += 2;
    currentActivity = "sleeping";
}

void SimGoblin::eat()
{
    if (status == "unhappy") {
        satiety += 2;
    }
    else {
        satiety += 5;
    }
    bladder += 2;
    currentActivity = "idle";
}

void SimGoblin::play()
{
    if (status == "unhappy") {
        fun += 2;
        currentActivity = "idle";
    }
    else {
        fun += 3;
        currentActivity = "playing";
    }
    rest -= 2;
}

void SimGoblin::pee()
{
    bladder = 0;
    hygene -= 2;
    currentActivity = "idle";
}

void SimGoblin::talk()
{
    if (status == "unhappy") {
        social += 2;
    }
    else {
        social += 3;
    }
    rest -= 1;
    currentActivity = "idle";
}

void SimGoblin::shower()
{
    if (status == "unhappy") {
        hygene += 2;
    }
    else {
        hygene += 4;
    }
    currentActivity = "showering";
}

void SimGoblin::clean()
{
    environment += 3;
    rest -= 2;
    currentActivity = "cleaning";
}

void SimGoblin::wait()
{
    currentActivity = "idle";
}

bool SimGoblin::isDead()
{
    return status == "dead";
}
