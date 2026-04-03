/*
Student Name: Jodie Elsa Soenarto
Student ID: 251103120132
Course: FITS1201 – Object Oriented Programming
Assignment: Final Project – Bingo-75 Game
Academic Integrity Declaration:
I declare that this work is my own and that I have not copied
code from other students, websites, or online repositories
without proper acknowledgement.
*/

#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip> // to help with the grid alignment with setw -- https://www.naukri.com/code360/library/setw-cpp
#include <string> // for string anc converting int to string -- https://www.geeksforgeeks.org/cpp/converting-number-to-string-in-cpp/
#define RESETCOLOR "\033[0m"
#define YELLOW  "\033[33m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define PURPLE "\033[35m"
#define LIGHT_BLUE "\033[36m"
using namespace std;

class Cards
{
private:
	int grid[5][5];
	bool markedPositions[5][5];

public:
	//Constructor
	Cards();

	//Getter
	// we MIGHT no need these getters
	//int getGridValue(int row, int col);
	//bool getMarkedStatus(int row, int col);

	//Function Members
	void generateCard();
	bool markNumber(int pulledNum);
	bool checkPatterns();
	void displayCards();

	//Importing
	void loadCardState(int loadedGrid[5][5], bool loadedMarked[5][5]);
	void getCardState(int outGrid[5][5], bool outMarked[5][5]);

};

#endif
