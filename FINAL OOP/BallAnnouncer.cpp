/********************************************************************
FITS1201 – Object-Oriented Programming
UNJI GAMES Assignment – Version 1
Academic Integrity Declaration
Student Name: Gabriella Renata Virgie
Student ID: 251103130115
Submission Date: Saturday, April 4 2026
I declare that:
1. This assignment is entirely my own original work.
2. I have not copied code from other students, websites, AI tools,
 or any external sources without proper acknowledgment.
3. I have not used AI tools (such as ChatGPT, GitHub Copilot, or similar)
 to generate any part of this assignment solution.
4. I have only used AI tools, if any, for learning purposes such as
 understanding concepts, syntax, or debugging, and not for generating
code.
5. Any concepts, syntax, or techniques not taught in this course have been
 properly acknowledged with citations in the comments of my code.
6. I understand that failure to comply with these requirements may result
 in academic misconduct proceedings and penalties, including a mark of
 zero for this assignment.
Student Signature: Gabriella Renata Virgie
********************************************************************/

#include "BallAnnouncer.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <limits>
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
	int choice = 0;

	do
	{
		cout << "\nSelect Difficulty\n";
		cout << "1. Hard (35 balls)\n";
		cout << "2. Medium (45 balls)\n";
		cout << "3. Easy (55 balls)\n";
		cout << "Enter choice: ";
		cin >> choice;

		if (choice < 1 || choice > 3|| cin.fail()) { //Checking if the input is valid or not. 
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Discard invalid input: https://gist.github.com/DerexScript/d4220fdd40203978f8ba80c0010fa970
			cout << "Invalid input. Please enter an integer (preferably 1-3).\n";
		}

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

	/* Refs:
	https://forum.qt.io/topic/157390/some-c-questions-about-using-random
	https://stackoverflow.com/questions/38367976/do-stdrandom-device-and-stdmt19937-follow-an-uniform-distribution
	*/
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
	displayRecent();
	cout << endl;
}

void BallAnnouncer::displayRecent(){
	cout << "Last 3 numbers: ";

	int count = drawnNumber.size();

	if (count == 0)
	{
		cout << "None\n";
		return;
	}

	//start from max(0, count - 3)
	int start = (count > 3) ? count - 3 : 0; //check to see if it's greater than 3. if so, then it'll display the last three item in the vector. refs: https://www.geeksforgeeks.org/cpp/cpp-ternary-or-conditional-operator/ and https://stackoverflow.com/questions/795286/what-does-the-question-mark-character-mean-in-c
	{

		for (int i = start; i < count; i++)
		{
			char letter;

			if (drawnNumber[i] <= 15) letter = 'B';
			else if (drawnNumber[i] <= 30) letter = 'I';
			else if (drawnNumber[i] <= 45) letter = 'N';
			else if (drawnNumber[i] <= 60) letter = 'G';
			else letter = 'O';

			cout << letter << "-" << drawnNumber[i] << " ";

		}

		cout << endl;
	}
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
	this_thread::sleep_for(chrono::milliseconds(50));          //Ref: https://www.geeksforgeeks.org/cpp/sleep-function-in-cpp/   genuinely a lifesaver

	for (int i = 0; i < 75; i++)
	{
		cout << "\x1b[2K";                                      //Deleting one line. Ref: https://stackoverflow.com/questions/61919292/c-how-do-i-erase-a-line-from-the-console#:~:text=2%20Answers,of%20lines%20to%20move%20up.
		cout << "\r";
		cout << "[" << Anim[i] << "]";
		this_thread::sleep_for(chrono::milliseconds(10));
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

vector<int> BallAnnouncer::getDrawnNumbers() {
	return drawnNumber;
}

int BallAnnouncer::getCurrentNumber() {
	return currentNumber;
}

void BallAnnouncer::loadAnnouncerState(const std::vector<int>&loadedDrawn, int loadedCurrent) {
	drawnNumber = loadedDrawn;     // Restores the history vector
	currentNumber = loadedCurrent; // Restores the number currently on screen
}
