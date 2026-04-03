/*
Student Name: Gabriella Renata Virgie
Student ID: 251103130115
Course: FITS1201 – Object Oriented Programming
Assignment: Final Project – Bingo-75 Game
Academic Integrity Declaration:
I declare that this work is my own and that I have not copied
code from other students, websites, or online repositories
without proper acknowledgement.
*/


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
	void displayRecent();          //show the 3 recent drawn numbers
    void rollingAnimation();       //rolling animation
	std::vector<int> getDrawnNumbers(); // to return the drawn numbers vector for saving/loading purposes
	int getCurrentNumber();         // to return the current number for saving/loading purposes
};

#endif
