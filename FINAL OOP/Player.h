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
	Cards generateCard();
	void displayCard();
	void markNumber(int number);

	//Player functions
	bool hasWon();
	void displayProfile();

	//Importing and Exporting cards
	void loadPlayerCard(int loadedGrid[5][5], bool loadedMarked[5][5]);
	void exportCardState(int outGrid[5][5], bool outMarked[5][5]);

};

#endif
