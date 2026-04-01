#ifndef BALLANNOUNCER_H
#define BALLANNOUNCER_H

#include <vector>
#include <string>

using namespace std;

class BallAnnouncer
{
private:
    vector<int>* ballPool;     //pointer to shuffled numbers 1–75
    vector<int> drawnNumber;   //numbers already drawn
    int currentNumber;
    int currentIndex;

public:
    int maxBalls;              //stops drawing at 35 / 45 / 55

    //Difficulty levels (depending on how hard it is to get a bingo)
    enum Difficulty
    {
        HARD = 35,
        MEDIUM = 45,
        EASY = 55
    };

    BallAnnouncer();                //constructor
    ~BallAnnouncer();               //destructor

    void setDifficulty();          //input + validation
    void resetPool();              //create a vector from 1–75 and shuffle
    int generateNumber();          //draw the next number
    void displayNumber();          //show the B/I/N/G/O letter + number
    void rollingAnimation();       //rolling animation
};

#endif
