#include "Player.h"
#include <iostream>

Player::Player() {
	playerName = "TBA";
	balance = 1000;
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
	 return balance;
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
	 cout << "Balance: " << balance << endl;
	 cout << "-------------------" << endl;

 }

 Player::~Player() {
	 delete[] cards;
 }
