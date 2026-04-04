/********************************************************************
FITS1201 – Object-Oriented Programming
Academic Integrity Declaration
Student Name: Jonathan Gouw Alexandrio
Student ID:   2511103130124
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
Student Signature: Jonathan Gouw Alexandrio
********************************************************************/

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
