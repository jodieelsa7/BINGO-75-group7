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
#include "FileManager.h"
#include <filesystem>   // to create directories
using namespace std;

// ================================================================
// CONSTRUCTOR
// Initializes the save directory location and file name.
// If the folder doesn't exist, it will be created automatically.
// ==============================================================
FileManager::FileManager(const string& directory, const string& file)
    : saveDirectory(directory), fileName(file)      // reference: https://en.cppreference.com/w/cpp/language/initializer_list.html
{
    std::filesystem::create_directories(saveDirectory);    // Create a directory to store game files and use the filesystem to run on all operating systems.
    cout << "[FileManager] Finish. File: " << saveDirectory + fileName << "\n";
}

// =================================================================
// DESTRUCTOR
// Closes the file if it is still open
// =============================================================
FileManager::~FileManager() {
    if (saveFile.is_open()) saveFile.close();
    if (loadFile.is_open()) loadFile.close();
}

// ==================================================================
// HELPER: getCurrentTimestamp
// Gets the current time in string format
// ================================================================
string FileManager::getCurrentTimestamp() {
    time_t now = time(nullptr);
    char buf[20];
    struct tm timeinfo;

    // Use the secure Microsoft version to prevent Visual Studio errors
    localtime_s(&timeinfo, &now);

    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);     // Reference: https://en.cppreference.com/w/cpp/chrono/c/strftime
    return string(buf);
}

// =================================================================
// saveProfile(): Creates the initial structure of the save file
// =============================================================
void FileManager::saveProfile() {
    string path = saveDirectory + fileName;

    saveFile.open(path);
    if (!saveFile.is_open()) {
        cerr << "[FileManager] ERROR: Cannot open file: " << path << "\n";
        return;
    }

    saveFile << "SAVED_AT=" << getCurrentTimestamp() << "\n";     // Timestamp save

    // Section structure
    saveFile << "[PLAYER]\n";
    saveFile << "[CURRENCY]\n";
    saveFile << "[GAME]\n";
    saveFile << "[BALLS]\n";
    saveFile << "[CARD]\n";

    saveFile.close();
    cout << "[FileManager] saveProfile() finish -> " << path << "\n";
}

// =================================================================
// loadProfile()
// Reading file contents (debugging)
// ===============================================================
void FileManager::loadProfile() {
    string path = saveDirectory + fileName;

    if (!fileExists()) {
        cerr << "[FileManager] ERROR: File not found : " << path << "\n";   // reference: https://gemini.google.com/share/aa0ba36e5a18
        return;
    }

    loadFile.open(path);
    if (!loadFile.is_open()) {
        cerr << "[FileManager] ERROR: Cannot open file: " << path << "\n";
        return;
    }

    string line;
    string currentSection = "";

    while (getline(loadFile, line)) {
        if (line.empty()) continue;

        // Detection section
        if (line[0] == '[') {
            currentSection = line;
            continue;
        }

        size_t pos = line.find('=');
        if (pos == string::npos) continue;

        string key = line.substr(0, pos);
        string val = line.substr(pos + 1);

        cout << "[FileManager] " << currentSection
            << " | " << key << " = " << val << "\n";
    }

    loadFile.close();
    cout << "[FileManager] loadProfile() finish.\n";
}

// ============================================================
// savePlayerData
// ============================================================
void FileManager::savePlayerData(const string& playerName, double balance) {
    string path = saveDirectory + fileName;

    saveFile.open(path, ios::app);
    if (!saveFile.is_open()) return;

    saveFile << "[PLAYER]\n";
    saveFile << "NAME=" << playerName << "\n";
    saveFile << "BALANCE=" << balance << "\n";

    saveFile.close();
    cout << "[FileManager] Player '" << playerName << "' saved.\n";
}

// ============================================================
// saveBallData
// ============================================================
void FileManager::saveBallData(const vector<int>& drawnNumbers,
    int currentNumber)
{
    string path = saveDirectory + fileName;

    saveFile.open(path, ios::app);
    if (!saveFile.is_open()) return;

    saveFile << "[BALLS]\n";
    saveFile << "CURRENT_NUMBER=" << currentNumber << "\n";
    saveFile << "DRAWN=";
    for (size_t i = 0; i < drawnNumbers.size(); i++) {
        saveFile << drawnNumbers[i];
        if (i < drawnNumbers.size() - 1) saveFile << ",";
    }
    saveFile << "\n";

    saveFile.close();
    cout << "[FileManager] Ball data is saved. Current: " << currentNumber << "\n";
}

void FileManager::saveCardData(const int grid[5][5],
    const bool marked[5][5])
{
    string path = saveDirectory + fileName;

    saveFile.open(path, ios::app);
    if (!saveFile.is_open()) return;

    saveFile << "[CARD]\n";

    saveFile << "GRID=";
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            saveFile << grid[i][j];
            if (!(i == 4 && j == 4)) saveFile << ",";
        }
    saveFile << "\n";

    // save marked
    saveFile << "MARKED=";
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            saveFile << marked[i][j];
            if (!(i == 4 && j == 4)) saveFile << ",";
        }
    saveFile << "\n";

    saveFile.close();
    cout << "[FileManager] Card data is saved.\n";
}

void FileManager::saveCurrencyData(double currentBalance, double lastWinAmount) {
    string path = saveDirectory + fileName;

    saveFile.open(path, ios::app);
    if (!saveFile.is_open()) return;

    saveFile << "[CURRENCY]\n";
    saveFile << "CURRENT_BALANCE=" << currentBalance << "\n";
    saveFile << "LAST_WIN_AMOUNT=" << lastWinAmount << "\n";

    saveFile.close();
    cout << "[FileManager] Currency disimpan. Balance: " << currentBalance << "\n";
}

void FileManager::saveGameData(double currentBet, int difficultyLevel) {
    string path = saveDirectory + fileName;

    saveFile.open(path, ios::app);
    if (!saveFile.is_open()) return;

    saveFile << "[GAME]\n";
    saveFile << "CURRENT_BET=" << currentBet << "\n";
    saveFile << "DIFFICULTY_LEVEL=" << difficultyLevel << "\n";

    saveFile.close();
    cout << "[FileManager] Game data saved.\n";
}

void FileManager::loadPlayerData(string& outName, double& outBalance) {
    string path = saveDirectory + fileName;
    loadFile.open(path);
    if (!loadFile.is_open()) return;

    string line;
    bool inSection = false;
    while (getline(loadFile, line)) {
        if (line == "[PLAYER]") { inSection = true;  continue; }
        if (!line.empty() && line[0] == '[') { inSection = false; continue; }
        if (!inSection) continue;

        size_t pos = line.find('=');
        if (pos == string::npos) continue;
        string key = line.substr(0, pos);
        string val = line.substr(pos + 1);

        if (key == "NAME")    outName = val;
        else if (key == "BALANCE") outBalance = stod(val);
    }

    loadFile.close();
    cout << "[FileManager] Player loaded: " << outName << "\n";
}

void FileManager::loadBallData(vector<int>& outDrawnNumbers,
    int& outCurrentNumber)
{
    string path = saveDirectory + fileName;
    loadFile.open(path);
    if (!loadFile.is_open()) return;

    string line;
    bool inSection = false;
    while (getline(loadFile, line)) {
        if (line == "[BALLS]") { inSection = true;  continue; }
        if (!line.empty() && line[0] == '[') { inSection = false; continue; }
        if (!inSection) continue;

        size_t pos = line.find('=');
        if (pos == string::npos) continue;
        string key = line.substr(0, pos);
        string val = line.substr(pos + 1);

        if (key == "CURRENT_NUMBER") {
            outCurrentNumber = stoi(val);
        }
        else if (key == "DRAWN" && !val.empty()) {
            outDrawnNumbers.clear();
            stringstream ss(val);
            string token;
            while (getline(ss, token, ','))
                outDrawnNumbers.push_back(stoi(token));
        }
    }

    loadFile.close();
    cout << "[FileManager] Ball loaded. Total: " << outDrawnNumbers.size() << "\n";
}

int FileManager::loadAllCardsData(vector<SavedCard>& loadedCards) {
    string path = saveDirectory + fileName;
    loadFile.open(path);
    if (!loadFile.is_open()) return 0;

    string line;
    bool inSection = false;

    SavedCard tempCard;
    bool hasGrid = false;
    bool hasMarked = false;

    while (getline(loadFile, line)) {
        if (line == "[CARD]") {
            inSection = true;
            hasGrid = false;
            hasMarked = false;
            continue;
        }
        if (!line.empty() && line[0] == '[') { inSection = false; continue; }
        if (!inSection) continue;

        size_t pos = line.find('=');
        if (pos == string::npos) continue;
        string key = line.substr(0, pos);
        string val = line.substr(pos + 1);

        if (key == "GRID" || key == "MARKED") {
            stringstream ss(val);   // Reference: https://en.cppreference.com/w/cpp/io/basic_stringstream.html
            string token;
            int idx = 0;
            while (getline(ss, token, ',') && idx < 25) {
                int row = idx / 5;
                int col = idx % 5;
                if (key == "GRID") {
                    tempCard.grid[row][col] = stoi(token);
                }
                if (key == "MARKED") {
                    tempCard.marked[row][col] = (token == "1");
                }
                idx++;
            }

            if (key == "GRID") hasGrid = true;
            if (key == "MARKED") hasMarked = true;

            // Once both GRID and MARKED are loaded for this section, save it to the list!
            if (hasGrid && hasMarked) {
                loadedCards.push_back(tempCard);
                hasGrid = false;
                hasMarked = false;
            }
        }
    }

    loadFile.close();
    cout << "[FileManager] Cards loaded: " << loadedCards.size() << "\n";
    return (int)loadedCards.size();
}

void FileManager::loadCurrencyData(double& outBalance, double& outLastWin) {
    string path = saveDirectory + fileName;
    loadFile.open(path);
    if (!loadFile.is_open()) return;

    string line;
    bool inSection = false;
    while (getline(loadFile, line)) {
        if (line == "[CURRENCY]") { inSection = true;  continue; }
        if (!line.empty() && line[0] == '[') { inSection = false; continue; }
        if (!inSection) continue;

        size_t pos = line.find('=');
        if (pos == string::npos) continue;
        string key = line.substr(0, pos);
        string val = line.substr(pos + 1);

        if (key == "CURRENT_BALANCE") outBalance = stod(val);   // Reference: https://en.cppreference.com/w/cpp/string/basic_string/stol
        else if (key == "LAST_WIN_AMOUNT") outLastWin = stod(val);
    }

    loadFile.close();
    cout << "[FileManager] Currency loaded. Balance: " << outBalance << "\n";
}

void FileManager::loadGameData(double& outBet, int& outDifficulty) {
    string path = saveDirectory + fileName;
    loadFile.open(path);
    if (!loadFile.is_open()) return;

    string line;
    bool inSection = false;
    while (getline(loadFile, line)) {
        if (line == "[GAME]") { inSection = true;  continue; }
        if (!line.empty() && line[0] == '[') { inSection = false; continue; }
        if (!inSection) continue;

        size_t pos = line.find('=');
        if (pos == string::npos) continue;
        string key = line.substr(0, pos);
        string val = line.substr(pos + 1);

        if (key == "CURRENT_BET")      outBet = stod(val);
        else if (key == "DIFFICULTY_LEVEL") outDifficulty = stoi(val);
    }

    loadFile.close();
    cout << "[FileManager] Game data loaded.\n";
}

// ============================================================
// fileExists
// ============================================================
bool FileManager::fileExists() {
    string path = saveDirectory + fileName;
    ifstream f(path);
    return f.good();
}

// =================================================================
// logEvent: Saves the log to a separate file: event_log.txt
// ===============================================================
void FileManager::logEvent(const string& eventDesc) {
    string path = saveDirectory + "event_log.txt";
    ofstream logFile(path, ios::app);
    if (!logFile.is_open()) return;
    logFile << "[" << getCurrentTimestamp() << "] " << eventDesc << "\n";
    logFile.close();
}

// =================================================================
// validateFile: Checks whether the file exists and is not empty
// ==============================================================
bool FileManager::validateFile() {
    string path = saveDirectory + fileName;
    ifstream f(path);

    if (!f.is_open()) {
        cout << "[FileManager] Validation FAILED: file not found.\n";
        return false;
    }

    f.seekg(0, ios::end);
    bool empty = (f.tellg() == 0);
    f.close();

    if (empty) {
        cout << "[FileManager] ValidationFAILED: empty file.\n";
        return false;
    }

    cout << "[FileManager] Validation OK.\n";
    return true;
}

void FileManager::readRules() {

    string path = saveDirectory + "rules.txt";

    ifstream file(path);
    if (!file.is_open()){
        cout<<"ERROR: Cannot open rules file\n";
        return;
    }

    string line;

    cout << "\n======== GAME RULES ==========\n";

    while (getline(file,line)) {
        cout << line <<endl;
    }

    cout <<"\n===============================\n";

    file.close();
}

