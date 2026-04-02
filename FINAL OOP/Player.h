#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Currency.h"
#include "Card.h"
using namespace std;

class Player {
private:
	string playerName;
	double balance;
	Card* cards;
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
	double getBalance() const;
	int getNumCards() const;

	//Card functions
	void generateCard(int n);
	void displayCard();
	void markNumber(int number);

	//Player functions
	bool hasWon();
	void displayProfile();

};

#endif
