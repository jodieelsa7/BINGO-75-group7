/********************************************************************
FITS1201 – Object-Oriented Programming
UNJI GAMES Assignment – Version 1
Academic Integrity Declaration
Student Name: Shintya Bella Purba
Student ID: 251103120135
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
Student Signature: <Shintya Bella Purba>
********************************************************************/

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

struct SavedCard {
    int grid[5][5] = { 0 };
    bool marked[5][5] = { false };
};

class FileManager {
private:
    std::ofstream saveFile;     // to WRITE data to file
    std::ifstream loadFile;     // to READ data from file

// --------------------------------------------------------
// ADDITIONAL ATTRIBUTES (not in UML but required)
// --------------------------------------------------------
    std::string saveDirectory;  // folder location: "saves/"
    std::string fileName;       // file name: "profile.txt"

    // --------------------------------------------------------
    // HELPER PRIVATE
    // --------------------------------------------------------
    std::string getCurrentTimestamp();  // Adding a timestamp to the activity log (via logEvent), so that every event in the program has time information

public:
    FileManager(const std::string& directory = "saves/",
                const std::string& file      = "profile.txt");
    ~FileManager();
    void saveProfile();     
    void loadProfile(); 
    void savePlayerData  (const std::string& playerName, double balance);
    void saveBallData    (const std::vector<int>& drawnNumbers, int currentNumber);
    void saveCardData    (const int grid[5][5], const bool marked[5][5]);
    void saveCurrencyData(double currentBalance, double lastWinAmount);
    void saveGameData    (double currentBet, int difficultyLevel);
    void loadPlayerData  (std::string& outName, double& outBalance);
    void loadBallData    (std::vector<int>& outDrawnNumbers, int& outCurrentNumber);
    int loadAllCardsData(std::vector<SavedCard>& loadedCards);
    void loadCurrencyData(double& outBalance, double& outLastWin);
    void loadGameData    (double& outBet, int& outDifficulty);
    void readRules();

    // Utility
    // Additional functions to assist FileManager operations
    bool fileExists();    // Checks if the save file already exists in the directory nd prevent errors when reading a non-existent file.
    void logEvent    (const std::string& eventDesc);    //Logs an event to a log file (event_log.txt), usually accompanied by a timestamp from getCurrentTimestamp() so that each activity has clear time information.
    bool validateFile();    //ensures the file's format and data are correct, thus preventing errors or crashes during loading.
};


#endif FILEMANAGER_H
