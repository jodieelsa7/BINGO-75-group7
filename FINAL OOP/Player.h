/*
Student Name: Nazla Alifa Jannatin
Student ID: 251103130125
Course: FITS1201 – Object Oriented Programming
Assignment: Final Project – Bingo-75 Game
Academic Integrity Declaration:
I declare that this work is my own and that I have not copied
code from other students, websites, or online repositories
without proper acknowledgement.
*/

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Currency.h"
#include "Cards.h"
using namespace std;

class Player {
private:
	string playerName;
	Currency balance;
	Cards* cards;
	int numCards;

public:
	//Constructor
	Player();

	//Destructor
	~Player();

	//Setters
	void setName(string name);
	void setBalance(double balance);

	//Getters
	string getName() const;
	Currency* retBalance();
	int getNumCards() const;

	//Card functions
	void generateCard(int n);
	void displayCard();
	void markNumber(int number);

	//Player functions
	bool hasWon();
	void displayProfile();

	//Importing and Exporting cards
	void loadPlayerCard(int index, int loadedGrid[5][5], bool loadedMarked[5][5]);
	void exportCardState(int index, int outGrid[5][5], bool outMarked[5][5]);

};

#endif
