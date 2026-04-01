#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;
class FileManager {
private:
ofstream saveFile;  

ifstream loadFile;  

// -----------------------
// ADDITIONAL ATTRIBUTES
// -----------------------
    string saveDirectory;   // storage folder location: "saves/"
    string fileName;        // file name used: "profile.txt"
// -----------------------
// HELPER PRIVATE
// -----------------------
string getCurrentTimestamp();

public:
    FileManager(const string& directory = "saves/",
        const string& file = "profile.txt");

    ~FileManager();

    void saveProfile();

    void loadProfile();

    void savePlayerData(const string& playerName, double balance);
    void saveBallData(const vector<int>& drawnNumbers, int currentNumber);
    void saveCardData(const int grid[5][5], const bool marked[5][5]);
    void saveCurrencyData(double currentBalance, double lastWinAmount);
    void saveGameData(double currentBet, int difficultyLevel);

    void loadPlayerData(string& outName, double& outBalance);
    void loadBallData(vector<int>& outDrawnNumbers, int& outCurrentNumber);
    void loadCardData(int grid[5][5], bool marked[5][5]);
    void loadCurrencyData(double& outBalance, double& outLastWin);
    void loadGameData(double& outBet, int& outDifficulty);

// Utility
bool fileExists();                          // cek apakah file save ada
void logEvent(const string& eventDesc);     // catat event ke log
bool validateFile();                         // cek file tidak kosong
