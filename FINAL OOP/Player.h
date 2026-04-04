/******************************************************************** 
FITS1201 – Object-Oriented Programming 
UNJI GAMES Assignment – Version 1 
Academic Integrity Declaration 
Student Name: Nazla Alifa Jannatin
Student ID: 251103130125
Submission Date: 4 April 2026
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
Student Signature: <Nazla Alifa Jannatin> 
********************************************************************/

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
