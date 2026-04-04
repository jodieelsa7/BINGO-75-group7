/*
Student Name: Jonathan Gouw Alexandrio
Student ID: 2511103130124
Course: FITS1201 – Object Oriented Programming
Assignment: Final Project – Bingo-75 Game
Academic Integrity Declaration:
I declare that this work is my own and that I have not copied
code from other students, websites, or online repositories
without proper acknowledgement.
*/
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H 

#include <vector>
#include <iostream>
#include "Player.h"
#include "BallAnnouncer.h"
#include "FileManager.h"


class GameManager {
private:
    std::vector<Player*> players;
    //std::vector<Cards> playerCards;
    BallAnnouncer announcer;
    FileManager fileSys;
    double totalPot;
    double currentBet;
    int difficulty;
    bool isMultiplayer;
    int noOfCards;

    // Helper methods for modularity
    void setupPlayers();
    void handleBetting();
    void saveGameState();
    bool checkAnyWinner();
    void processWinner(Player* winner);
    bool inGameMenu();

public:
    GameManager();
    ~GameManager();

    void startGame(); // Entry point: Login/Register & Setup
    void mainLoop();  // The active game phase
};

#endif
