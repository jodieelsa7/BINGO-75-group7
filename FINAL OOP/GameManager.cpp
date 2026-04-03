/*
Student Name: Jonathan Gouw Alexandrio
Student ID: 251103130124
Course: FITS1201 – Object Oriented Programming
Assignment: Final Project – Bingo-75 Game
Academic Integrity Declaration:
I declare that this work is my own and that I have not copied
code from other students, websites, or online repositories
without proper acknowledgement.
*/

#include "GameManager.h"

GameManager::GameManager() : totalPot(0), difficulty(2), isMultiplayer(false) {}

GameManager::~GameManager() {
    for (Player* p : players) delete p;
    players.clear();
}

void GameManager::startGame() {
    int choice;
    std::cout << "1. Login to Existing Profile\n" 
              << "2. Create New Profile\n"
              << "Choice: ";
    std::cin >> choice;

    if (choice == 1 && fileSys.validateFile()) {
        std::string loadedName;
        double loadedBalance;
        fileSys.loadPlayerData(loadedName, loadedBalance);

        std::cout << "\n===================================\n";
        std::cout << "Welcome back, " << loadedName << "!\n";
        std::cout << "Current Balance: " << loadedBalance << " credits\n";
        std::cout << "===================================\n";

        double savedPot = 0;
        int savedDiff = 0;
        fileSys.loadGameData(savedPot, savedDiff);

        // CHECK FOR UNFINISHED GAME
        if (savedPot > 0) {
            char resume;
            std::cout << ">> You have an unfinished game with a pot of " << savedPot << " credits.\n";
            std::cout << ">> Do you want to resume it? (y/n): ";
            std::cin >> resume;

            if (resume == 'y' || resume == 'Y') {
                // Resume logic
                this->totalPot = savedPot;
                this->difficulty = savedDiff;

                Player* p = new Player();
                p->setName(loadedName);
                p->setBalance(loadedBalance);

                // Load the exact card markings from the file
                int grid[5][5];
                bool marked[5][5];
                fileSys.loadCardData(grid, marked);
                p->loadPlayerCard(grid, marked);

                players.push_back(p);
                isMultiplayer = false;

                std::cout << "\nGame resumed successfully! Good luck!\n";
                mainLoop();
                return; // Skips the new game setup below
            }
            else {
                std::cout << "Abandoning old game. Wiping previous pot...\n";
                totalPot = 0;
            }
        }

        // If they chose not to resume, or no game was saved, start fresh with loaded profile
        Player* p = new Player();
        p->setName(loadedName);
        p->setBalance(loadedBalance);
		fileSys.saveProfile(); // Update the file with the loaded profile (in case of any discrepancies)

        //Gives the player more credits if they do not have enough to bet for the next game.
        if (p-> retBalance()->getBalance() < 10) {
            char choice;
            std::cout << "Insufficient balance to start a new game. Would you like to add more credits?\n";
			std::cin >> choice;
			if (choice == 'y' || choice == 'Y') {
                double amount;
                std::cout << "Enter amount to add: ";
                std::cin >> amount;
                p-> retBalance()->addWins(amount);
                std::cout << "New Balance: " << p-> retBalance()->getBalance() << " credits\n";
            }
            else //nothing will happen
            return;
		}
        players.push_back(p);
        isMultiplayer = false;

        int cardsChoice;
        std::cout << "How many cards do you want? (up to 4): ";
        std::cin >> cardsChoice;
        for (int i = 0; i < cardsChoice; i++) {
            playerCards.push_back(p->generateCard());
		}

        announcer.setDifficulty();
        handleBetting();

    }
    else {
        // Brand New Profile Setup
        setupPlayers();
        announcer.setDifficulty();
        handleBetting();
    }

    mainLoop(); // Start the actual game loop
}

void GameManager::setupPlayers() {
    int numPlayers;
    std::cout << "Enter number of players (1-4): ";
    std::cin >> numPlayers;
    isMultiplayer = (numPlayers > 1);

    for (int i = 0; i < numPlayers; i++) {
        std::string name;
        std::cout << "Player " << (i + 1) << " Name: ";
        std::cin >> name;

        Player* p = new Player();
        p->setName(name);
        if (!isMultiplayer) {
            std::cout << "How many cards do you want? (up to 4): ";
            std::cin >> noOfCards;
            for (int i = 0; i < noOfCards; i++) {
                playerCards.push_back(p->generateCard());
            }
        }
        else playerCards.push_back(p->generateCard());

        // Ensure player has enough balance to play 
        if (p-> retBalance()->getBalance() < 10) {
            std::cout << "Insufficient balance for " << name << ". Redirecting to menu." << std::endl;
            return;
        }
        players.push_back(p);
    }
}

void GameManager::handleBetting() {
    for (Player* p : players) {
        double bet;
        std::cout << p->getName() << ", enter bet (multiples of 10): ";
        std::cin >> bet;
        p-> retBalance()->subtractLoss(bet);
        totalPot += bet;
        currentBet = bet;
    }
}

void GameManager::processWinner(Player* winner) {
    double multiplier = 0;
    // Determine multiplier based on BallAnnouncer's maxBalls
    if (announcer.maxBalls == 35) multiplier = 5.0;
    else if (announcer.maxBalls == 45) multiplier = 3.0;
    else multiplier = 2.0;

    double reward = 0;
    if (isMultiplayer) {
        reward = totalPot; // Winner takes the cumulative pot
    }
    else {
        reward = currentBet * multiplier; // Singleplayer uses multiplier
    }

    winner->retBalance()->addWins(reward);
    std::cout << "BINGO! " << winner->getName() << " won " << reward << " credits!" << std::endl;
}

void GameManager::mainLoop() {
    bool gameOver = false;
    while (!gameOver) {
        int choice;
        std::cout << "\n1. Draw Number\n2. Save & Quit\nChoice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::system("cls");
            //std::cout << "\033[2J\033[H";
            int drawn = announcer.generateNumber();
            if (drawn == -1) {
                std::cout << "Game Over: No more balls!\n";
                gameOver = true;
                break;
            }
            announcer.rollingAnimation();
            announcer.displayNumber();

            for (Player* p : players) {
                p->markNumber(drawn);
                if (noOfCards > 1) {
					std::cout << p->getName() << "'s Cards:\n";
                    for (int i = 0; i < noOfCards; i++) {
                        playerCards[i].markNumber(drawn);
                        playerCards[i].displayCards();
					}
				}
                else {
                    playerCards[0].markNumber(drawn);
                    playerCards[0].displayCards();
                };
                if (p->hasWon()) {
                    std::cout << "BINGO! " << p->getName() << " wins " << totalPot << "!\n";
                    processWinner(p);
                    gameOver = true;

                }
            }
            break;
        }
        case 2:
            saveGameState();
            gameOver = true;
            break;
        }
    }
}

void GameManager::saveGameState() {
    //Overwrite the old file to create a fresh save structure
    fileSys.saveProfile();

    //Save the unfinished game pot and difficulty
    fileSys.saveGameData(totalPot, difficulty);

    //Save the announced balls and the current number
    fileSys.saveBallData(announcer.getDrawnNumbers(), announcer.getCurrentNumber());

    // Save the player's info and card state
    for (Player* p : players) {
        fileSys.savePlayerData(p->getName(), p->retBalance()->getBalance());

        if (p->getNumCards() > 0) {
            int grid[5][5];
            bool marked[5][5];
            p->exportCardState(grid, marked); // Grab the arrays from Player
            fileSys.saveCardData(grid, marked); // Write them to profile.txt
        }
        break; // Save only Player 1 for single-player profile continuation
    }
    std::cout << "Game Progress Saved securely to your profile.\n";
}
