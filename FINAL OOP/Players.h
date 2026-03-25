#include <iostream>
#include <string>
#include "Cards.h"
#include "Currency.h"
using namespace std;

class Players
{
private:
	int noOfPlayers;
	string playerName;
	vector<Cards> playerCards; 
	Currency playerBalance;

public: 
	//Constructor
	Players();

	//Destructor
	~Players();

	//Setters
	void setPlayerName(string);

	//Getters
	string getPlayerName();

	// Function Member
	void createCard();
	void updateCards(int number);
	bool playerHasWon();


};

