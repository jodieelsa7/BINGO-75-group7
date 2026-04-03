#include "FileManager.h"
#include <filesystem>   // to create directories
using namespace std;

// ================================================================
// CONSTRUCTOR
// Initializes the save directory location and file name.
// If the folder doesn't exist, it will be created automatically.
// ==============================================================
FileManager::FileManager(const string& directory, const string& file)
    : saveDirectory(directory), fileName(file)
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
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

// =================================================================
// saveProfile(): Creates the initial structure of the save file
// =============================================================
void FileManager::saveProfile(const string& playerName, double balance, 
                               const vector<int>& drawnNumbers, int currentNumber,
                               const int grid[5][5], const bool marked[5][5],
                               double currentBet, int difficulty) 
{
    string path = saveDirectory + playerName + ".txt";

    saveFile.open(path);
    if (!saveFile.is_open()) {
        cerr << "[FileManager] ERROR: Cannot open file: " << path << "\n";
        return;
    }

    saveFile << "SAVED_AT=" << getCurrentTimestamp() << "\n";     // Timestamp save
    
    // Section structure
    saveFile << "[PLAYER]\nNAME=" << playerName << "\nBALANCE=" << balance << "\n";

    // Save Data Bola
    saveFile << "[BALLS]\nCURRENT=" << currentNumber << "\nDRAWN=";
    for (size_t i = 0; i < drawnNumbers.size(); i++) {
        saveFile << drawnNumbers[i] << (i < drawnNumbers.size() - 1 ? "," : "");
    }
    saveFile << "\n";

    // Save Data Kartu (Grid & Marked)
    saveFile << "[CARD]\nGRID=";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            saveFile << grid[i][j] << (!(i == 4 && j == 4) ? "," : "");
        }
    }
    saveFile << "\nMARKED=";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            saveFile << (marked[i][j] ? "1" : "0") << (!(i == 4 && j == 4) ? "," : "");
        }
    }
    saveFile << "\n";

    // Save Data Game
    saveFile << "[GAME]\nBET=" << currentBet << "\nDIFFICULTY=" << difficulty << "\n"
    saveFile.close();
    cout << "[FileManager] Successfully saved profile to: " << path << "\n";
}

// =================================================================
// loadProfile()
// Reading file contents (debugging)
// ===============================================================
void FileManager::loadProfile(const string& playerName, double& outBalance, 
                               vector<int>& outDrawnNumbers, int& outCurrentNumber,
                               int grid[5][5], bool marked[5][5],
                               double& outBet, int& outDifficulty) 
{
    string path = saveDirectory + playerName + ".txt";

    loadFile.open(path);
    if (!loadFile.is_open()) {
        cerr << "[FileManager] ERROR: Cannot open file: " << path << "\n";
        return;
    }

    string line, section;
    while (getline(loadFile, line)) {
        if (line.empty()) continue;

        // Detection section
        if (line[0] == '[') { section = line;
            continue;
        }

        size_t pos = line.find('=');
        if (pos == string::npos) continue;
        string key = line.substr(0, pos);
        string val = line.substr(pos + 1);
if (section == "[PLAYER]" && key == "BALANCE") outBalance = stod(val);
        else if (section == "[BALLS]") {
            if (key == "CURRENT") outCurrentNumber = stoi(val);
            else if (key == "DRAWN") {
                outDrawnNumbers.clear();
                stringstream ss(val);
                string t;
                while (getline(ss, t, ',')) outDrawnNumbers.push_back(stoi(t));
            }
        }
        else if (section == "[CARD]") {
            stringstream ss(val);
            string t;
            int idx = 0;
            while (getline(ss, t, ',') && idx < 25) {
                if (key == "GRID") grid[idx/5][idx%5] = stoi(t);    // (stoi means string to integers)
else if (key == "MARKED") marked[idx/5][idx%5] = (t == "1");
                idx++;
            }
        }
        else if (section == "[GAME]") {
            if (key == "BET") outBet = stod(val);
            else if (key == "DIFFICULTY") outDifficulty = stoi(val);
        }
    }
    loadFile.close();
    cout << "[FileManager] Profil '" << playerName << "' successfully loaded.\n";
}

bool FileManager::fileExists(const string& playerName) {
ifstream f(saveDirectory + playerName + ".txt");
    return f.good();
}
        
