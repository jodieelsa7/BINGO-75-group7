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

#include "Player.h"
#include <iostream>

Player::Player() : balance(100.0) {
	playerName = "TBA";
	cards = nullptr;
	numCards = 0;

}

void Player::setName(string name) {
	playerName = name;

}

void Player::setBalance(double newBalance) {
	balance = newBalance;
}

string Player::getName() const {
	return playerName;
}

Currency* Player::retBalance() {
	return &balance;
}

int Player::getNumCards() const {
	return numCards;
}

void Player::generateCard(int n) {
	delete[] cards;              
	numCards = n;                
	cards = new Cards[numCards];
}

void Player::displayCard() {
	for (int i = 0; i < numCards; i++) {
		cards[i].displayCards();
	}
}

void Player::markNumber(int number) {
	for (int i = 0; i < numCards; i++) {
		cards[i].markNumber(number);
	}
}

bool Player::hasWon() {
	for (int i = 0; i < numCards; i++) {
		if (cards[i].checkPatterns()) {
			return true;
		}
	}
	return false;
}

void Player::displayProfile() {
	cout << "-------------------" << endl;
	cout << "Name: " << playerName << endl;
	cout << "Balance: " << balance.getBalance() << endl;
	cout << "-------------------" << endl;

}

void Player::loadPlayerCard(int index, int loadedGrid[5][5], bool loadedMarked[5][5]) {
	// Ensure the player has at least 1 card allocated before injecting data
	if (index < numCards) {
		cards[index].loadCardState(loadedGrid, loadedMarked);
	}
}

void Player::exportCardState(int index, int outGrid[5][5], bool outMarked[5][5]) {
	if (index < numCards) {
		cards[index].getCardState(outGrid, outMarked);
	}
}

Player::~Player() {
	delete[] cards;
}
