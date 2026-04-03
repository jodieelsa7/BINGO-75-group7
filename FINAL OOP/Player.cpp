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

Cards Player::generateCard() {
	cards = new Cards;
	return *cards;

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

void Player::loadPlayerCard(int loadedGrid[5][5], bool loadedMarked[5][5]) {
	// Ensure the player has at least 1 card allocated before injecting data
	if (numCards == 0) { generateCard(); }
	cards[0].loadCardState(loadedGrid, loadedMarked);
}

void Player::exportCardState(int outGrid[5][5], bool outMarked[5][5]) {
	if (numCards > 0) {
		cards[0].getCardState(outGrid, outMarked);
	}
}

Player::~Player() {
	delete[] cards;
}
