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
#include "GameManager.h"

GameManager::GameManager() : totalPot(0), difficulty(2), isMultiplayer(false), noOfCards(1) {}

GameManager::~GameManager() {
    for (Player* p : players) delete p;
    players.clear();
}

void GameManager::startGame() {
    int choice;
    std::cout << "1. Login to Existing Profile\n"  
              << "2. Create New Profile\n"
              << "3. View Game Rules\n"
              << "4. Quit\n"
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
                std::vector<SavedCard> savedCards;
                int loadedCardCount = fileSys.loadAllCardsData(savedCards);

                if (loadedCardCount > 0) {
                    p->generateCard(loadedCardCount); // Tell Player to make enough room
                    this->noOfCards = loadedCardCount;

                    // Inject the data into every card using our vector!
                    for (int i = 0; i < loadedCardCount; i++) {
                        p->loadPlayerCard(i, savedCards[i].grid, savedCards[i].marked);
                    }
                }
                else {
                    p->generateCard(1); // Safe fallback
                    this->noOfCards = 1;
                }

				// loads the drawn numbers and current number into the announcer
                std::vector<int> loadedDrawn;
                int loadedCurrent = 0;
                fileSys.loadBallData(loadedDrawn, loadedCurrent);
                announcer.loadAnnouncerState(loadedDrawn, loadedCurrent);

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
		p->generateCard(cardsChoice);

        announcer.setDifficulty();
        handleBetting();

    }
    else if (choice == 2) {
        // Brand New Profile Setup
        setupPlayers();
        announcer.setDifficulty();
        handleBetting();
    }

    else if (choice == 3) {
        fileSys.readRules();
        std::cout<<"Press ENTER to return to the menu\n";
        cin.ignore();
        cin.get();
    }

    else if (choice == 4) {
        break;
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
            p->generateCard(noOfCards);
        }
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

bool GameManager::inGameMenu() {
    int choice;
    while (true) {
        std::cout << "\n===================================\n";
        std::cout << "             MAIN MENU             \n";
        std::cout << "===================================\n";

		for (Player* p : players)
		p->displayProfile();

        std::cout << "1. Continue Playing\n";
        std::cout << "2. Save and Quit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "\nReturning to the game...\n";
            // Re-display the board so the player can re-orient themselves
            announcer.displayNumber();
            for (Player* p : players) {
                p->displayCard();
            }
            return true; // Tells the mainLoop to keep going
        }
        else if (choice == 2) {
            saveGameState(); // Final save before exiting
            return false;    // Tells the mainLoop to trigger Game Over
        }
        else {
            std::cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    }
}

void GameManager::mainLoop() {
    bool manualQuit = false;
    bool playAgain = true;

    while (playAgain) {
        bool gameOver = false;
        while (!gameOver) {
            int choice;
            std::cout << "\n1. Draw Number\n2. Return to main menu\nChoice: ";
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
                    p->markNumber(drawn); // Automatically marks all of the player's cards
                    p->displayCard();     // Automatically prints all of the player's cards perfectly!

                    if (p->hasWon()) {    // Automatically checks all of the player's cards
                        std::cout
                            << "888      d8b                         " << "\n"
                            << "888      Y8P                         " << "\n"
                            << "888                                 " << "\n"
                            << "88888b.  888 88888b.  .d88b.     .d88b.  " << "\n"
                            << "888  \"88b888 88   88bd88P  \"88bd88\"  \"88b " << "\n"
                            << "888   888888 888  888888    88888.    888 " << "\n"
                            << "888  d88P888 888  888Y88b   888Y88.  .88P " << "\n"
                            << "88888P\"  888 888  888 \"Y888888P  \"Y88P\"		" << "\n"
                            << "                            888         " << "\n"
                            << "                       Y8b d88P        " << "\n"
                            << "                        \"Y88P\"" << "\n"
                            ;
                        processWinner(p);
                        gameOver = true;
                    }
                }
                break;
            }
            case 2:
                std::cout << "\nSaving current progress...\n";
                saveGameState();
                if (!inGameMenu()) {
                    gameOver = true;
                    manualQuit = true;
                }
                break;
            }
        }
        if (manualQuit) {
            std::cout << "Thanks for playing! Goodbye!\n";
            playAgain = false;
            break;
        }
        else {
            char replayChoice;
            std::cout << "\nDo you want to play again? (y/n): ";
            std::cin >> replayChoice;
			if (replayChoice == 'y' || replayChoice == 'Y') {
                // Reset game state for a new game
                announcer.resetPool();
                totalPot = 0;
                for (Player* p : players) {
                    if (p->retBalance()->getBalance() < 10) {
                        std::cout << p->getName() << " has insufficient balance to continue. Please add more credits.\n";
                        double amount;
                        std::cout << "Enter amount to add for " << p->getName() << ": ";
                        std::cin >> amount;
                        p-> retBalance()->addWins(amount);
						std::cout << "New Balance: " << p->retBalance()->getBalance() << " credits\n";
                    }
                    p->generateCard(noOfCards); // Regenerate cards with the same number of cards as before
                }
                announcer.setDifficulty();
				handleBetting();
            }
            else {
                fileSys.saveProfile();
                for (Player* p : players) fileSys.savePlayerData(p->getName(), p->retBalance()->getBalance());
                std::cout << "Thanks for playing! Goodbye!\n";
                playAgain = false;
            }
        }
    }
};

void GameManager::saveGameState() {
    //Overwrite the old file to create a fresh save structure
    fileSys.saveProfile();

    //Save the unfinished game pot and difficulty
    fileSys.saveGameData(totalPot, difficulty);

    //Save the announced balls and the current number
    fileSys.saveBallData(announcer.getDrawnNumbers(), announcer.getCurrentNumber());

    //Save the player's info and card state
    for (Player* p : players) {
        fileSys.savePlayerData(p->getName(), p->retBalance()->getBalance());

        if (p->getNumCards() > 0) {
            for (int i = 0; i < p->getNumCards(); i++) {
                int grid[5][5];
                bool marked[5][5];
                p->exportCardState(i, grid, marked);
                fileSys.saveCardData(grid, marked);
            }
        }
        break; // Save only Player 1 for single-player profile continuation
    }
    std::cout << "Game Progress Saved securely to your profile.\n";
} 

