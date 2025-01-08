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
    if (rest <= 0) {
        rest = 0;
    }
    if (rest >= 10) {
        rest = 10;
    }
    --hunger;
    if (hunger <= 0) {
        hunger = 0;
    }
    if (hunger >= 10) {
        hunger = 10;
    }
    --fun;
    if (fun <= 0) {
        fun = 0;
    }
    if (fun >= 10) {
        fun = 10;
    }
    --bladder;
    if (bladder <= 0) {
        bladder = 0;
    }
    if (bladder >= 10) {
        bladder = 10;
    }
    --social;
    if (social <= 0) {
        social = 0;
    }
    if (social >= 10) {
        social = 10;
    }
    --hygene;
    if (hygene <= 0) {
        hygene = 0;
    }
    if (hygene >= 10) {
        hygene = 10;
    }
    --environment;
    if (environment <= 0) {
        environment = 0;
    }
    if (environment >= 10) {
        environment = 10;
    }

    if (rest <= 3 || hunger <= 3 || fun <= 3 || bladder <= 3 ||
        social <= 3 || hygene <= 3 || environment <= 3) {
        status = "unhappy";
    }
    else if (rest <= 0 || hunger <= 0 ) {
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
        hunger += 2;
    }
    else {
        hunger += 5;
    }
    bladder -= 2;
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
    bladder = 10;
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
