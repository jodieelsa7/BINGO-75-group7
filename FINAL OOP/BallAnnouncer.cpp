#include "BallAnnouncer.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

//Constructor
BallAnnouncer::BallAnnouncer()
{
    ballPool = new vector<int>;
    currentIndex = 0;
    currentNumber = 0;
    maxBalls = HARD;
    resetPool();
}

//Destructor
BallAnnouncer::~BallAnnouncer()
{
    delete ballPool;
}

//Ask the user for difficulty (with validation for it)
void BallAnnouncer::setDifficulty()
{
    int choice;

    do
    {
        cout << "\nSelect Difficulty\n";
        cout << "1. Hard (35 balls)\n";
        cout << "2. Medium (45 balls)\n";
        cout << "3. Easy (55 balls)\n";
        cout << "Enter choice: ";
        cin >> choice;

    } while (choice < 1 || choice > 3);

    if (choice == 1) maxBalls = HARD;
    else if (choice == 2) maxBalls = MEDIUM;
    else if (choice == 3) maxBalls = EASY;
}

//fill the vector from 1–75 and shuffle it
void BallAnnouncer::resetPool()
{
    ballPool->clear();
    drawnNumber.clear();
    currentIndex = 0;

    for (int i = 1; i <= 75; i++)
    {
        ballPool->push_back(i);
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(ballPool->begin(), ballPool->end(), g);
}

//Generate next number but stop at difficulty limit
int BallAnnouncer::generateNumber()
{
    if (currentIndex >= maxBalls)
    {
        cout << "\nReached difficulty limit.\n";
        return -1;
    }


    else
    {
        currentNumber = (*ballPool)[currentIndex];
        drawnNumber.push_back(currentNumber);
        currentIndex++;

        return currentNumber;
    }


}

//Display number with the BINGO letter
void BallAnnouncer::displayNumber()
{
    char letter;

    if (currentNumber >= 1 && currentNumber <= 15) letter = 'B';
    else if (currentNumber <= 30) letter = 'I';
    else if (currentNumber <= 45) letter = 'N';
    else if (currentNumber <= 60) letter = 'G';
    else letter = 'O';

    cout << "\nNumber drawn: " << letter << " - " << currentNumber << endl;
}

//Animation
void BallAnnouncer::rollingAnimation()
{
    vector<int> Anim;

    for (int i = 1; i <= 75; i++)                               //This is just a "fake" vector so i can make it look like it's scrolling through the numbers
    {
        Anim.push_back(i);
    }

    cout << "\n\nRolling the numbers. . . " << endl;            //Tried usinng <windows.h>, but it didnt work for some reason so i use an alternative
    this_thread::sleep_for(chrono::milliseconds(200));          //Ref: https://www.geeksforgeeks.org/cpp/sleep-function-in-cpp/   genuinely a lifesaver

    for (int i = 0; i < 75; i++)
    {
        cout << "\x1b[2K";                                      //Deleting one line. Ref: https://stackoverflow.com/questions/61919292/c-how-do-i-erase-a-line-from-the-console#:~:text=2%20Answers,of%20lines%20to%20move%20up.
        cout << "\r";
        cout << "[" << Anim[i] << "]";
        this_thread::sleep_for(chrono::milliseconds(20));
    }

    cout << "\x1b[2K";
    for (int i = 1; i < 2; i++) {
        cout
            << "\x1b[1A"
            << "\x1b[2K";
    }
    cout << "\r";
    cout << "[" << currentNumber << "]";                        //To display the actual rolled number
}
