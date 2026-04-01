#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

class FileManager {
private:
    std::ofstream saveFile;     
    std::ifstream loadFile;     

// --------------------------------------------------------
// ADDITIONAL ATTRIBUTES (not in UML but required)
// --------------------------------------------------------
    std::string saveDirectory;  // folder location: "saves/"
    std::string fileName;       // file name: "profile.txt"

    // --------------------------------------------------------
    // HELPER PRIVATE
    // --------------------------------------------------------
    std::string getCurrentTimestamp();  

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
    void loadCardData    (int grid[5][5], bool marked[5][5]);
    void loadCurrencyData(double& outBalance, double& outLastWin);
    void loadGameData    (double& outBet, int& outDifficulty);

    // Utility
    bool fileExists();
    void logEvent    (const std::string& eventDesc);
    bool validateFile();
};
