#include "Player.h"
#include <iostream>

Player::Player() balance(100.0) {
	playerName = "TBA";
	cards = nullptr;
	numCards = 0;
}

 void Player::setName(string name) {
	 playerName = name;
}

 void Player::setBalance(double newbalance) {
	 balance = newbalance;
 }

 string Player::getName() const {
	 return playerName;
 }

 double Player::getBalance() const { 
	 return balance.getBalance();
 }

 void Player::addBalance(int amount) {
	 balance.addWins(amount);
 }

 void Player::deductBalance(int amount) {
	 balance.subtractLoss(amount);
 }

 int Player::getNumCards() const {
	 return numCards;
 }

 void Player::generateCard(int n) {
	 delete[] cards;
	 numCards = n;
	 cards = new Card[numCards];

 }

 void Player::displayCard() {
	 for (int i = 0; i < numCards; i++) {
		 cards[i].displayCard();
	 }
 }

 void Player::markNumber(int number) {
	 for (int i = 0; i < numCards; i++) {
		 cards[i].markNumber(number);
	 }
 }

 bool Player::hasWon() {
	 for (int i = 0; i < numCards; i++) {
		 if (cards[i].hasWon()) {
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

 Player::~Player() {
	 delete[] cards;
 }
