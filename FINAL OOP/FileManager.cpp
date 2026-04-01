#include "FileManager.h"
using namespace std;

FileManager::FileManager(const string& directory, const string& file)
    : saveDirectory(directory), fileName(file)
{
    system(("mkdir -p " + saveDirectory).c_str());
    cout << "[FileManager] Siap. File: " << saveDirectory + fileName << "\n";
}

FileManager::~FileManager() {
    if (saveFile.is_open()) saveFile.close();
    if (loadFile.is_open()) loadFile.close();
}

string FileManager::getCurrentTimestamp() {
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

void FileManager::saveProfile() {
    string path = saveDirectory + fileName;

    saveFile.open(path);
    if (!saveFile.is_open()) {
        cerr << "[FileManager] ERROR: Tidak bisa membuka file: " << path << "\n";
        return;
    }

    saveFile << "SAVED_AT=" << getCurrentTimestamp() << "\n";
    saveFile << "[PLAYER]\n";
    saveFile << "[CURRENCY]\n";
    saveFile << "[GAME]\n";
    saveFile << "[BALLS]\n";
    saveFile << "[CARD]\n";

    saveFile.close();
    cout << "[FileManager] saveProfile() selesai -> " << path << "\n";
}

void FileManager::loadProfile() {
    string path = saveDirectory + fileName;

    if (!fileExists()) {
        cerr << "[FileManager] ERROR: File tidak ditemukan: " << path << "\n";
        return;
    }

    loadFile.open(path);
    if (!loadFile.is_open()) {
        cerr << "[FileManager] ERROR: Tidak bisa membuka file: " << path << "\n";
        return;
    }

    string line;
    string currentSection = "";

    while (getline(loadFile, line)) {
        if (line.empty()) continue;

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
    cout << "[FileManager] loadProfile() selesai.\n";
}

void FileManager::savePlayerData(const string& playerName, double balance) {
    string path = saveDirectory + fileName;
    saveFile.open(path, ios::app);
    if (!saveFile.is_open()) return;

    saveFile << "[PLAYER]\n";
    saveFile << "NAME="    << playerName << "\n";
    saveFile << "BALANCE=" << balance    << "\n";

    saveFile.close();
    cout << "[FileManager] Player '" << playerName << "' disimpan.\n";
}

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
    cout << "[FileManager] Data bola disimpan. Current: " << currentNumber << "\n";
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

    saveFile << "MARKED=";
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            saveFile << marked[i][j];
            if (!(i == 4 && j == 4)) saveFile << ",";
        }
    saveFile << "\n";

    saveFile.close();
    cout << "[FileManager] Data kartu disimpan.\n";
}

void FileManager::saveCurrencyData(double currentBalance, double lastWinAmount) {
    string path = saveDirectory + fileName;
    saveFile.open(path, ios::app);
    if (!saveFile.is_open()) return;

    saveFile << "[CURRENCY]\n";
    saveFile << "CURRENT_BALANCE=" << currentBalance  << "\n";
    saveFile << "LAST_WIN_AMOUNT=" << lastWinAmount   << "\n";

    saveFile.close();
    cout << "[FileManager] Currency disimpan. Balance: " << currentBalance << "\n";
}

void FileManager::saveGameData(double currentBet, int difficultyLevel) {
    string path = saveDirectory + fileName;
    saveFile.open(path, ios::app);
    if (!saveFile.is_open()) return;

    saveFile << "[GAME]\n";
    saveFile << "CURRENT_BET="      << currentBet      << "\n";
    saveFile << "DIFFICULTY_LEVEL=" << difficultyLevel << "\n";

    saveFile.close();
    cout << "[FileManager] Game data disimpan.\n";
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

        if      (key == "NAME")    outName    = val;
        else if (key == "BALANCE") outBalance = stod(val);
    }

    loadFile.close();
    cout << "[FileManager] Player dimuat: " << outName << "\n";
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
        } else if (key == "DRAWN" && !val.empty()) {
            outDrawnNumbers.clear();
            stringstream ss(val);
            string token;
            while (getline(ss, token, ','))
                outDrawnNumbers.push_back(stoi(token));
        }
    }

    loadFile.close();
    cout << "[FileManager] Bola dimuat. Total: " << outDrawnNumbers.size() << "\n";
}

void FileManager::loadCardData(int grid[5][5], bool marked[5][5]) {
    string path = saveDirectory + fileName;
    loadFile.open(path);
    if (!loadFile.is_open()) return;

    string line;
    bool inSection = false;
    while (getline(loadFile, line)) {
        if (line == "[CARD]") { inSection = true;  continue; }
        if (!line.empty() && line[0] == '[') { inSection = false; continue; }
        if (!inSection) continue;

        size_t pos = line.find('=');
        if (pos == string::npos) continue;
        string key = line.substr(0, pos);
        string val = line.substr(pos + 1);

        if (key == "GRID" || key == "MARKED") {
            stringstream ss(val);
            string token;
            int idx = 0;
            while (getline(ss, token, ',') && idx < 25) {
                int row = idx / 5;
                int col = idx % 5;
                if (key == "GRID")   grid[row][col]   = stoi(token);
                if (key == "MARKED") marked[row][col] = (token == "1");
                idx++;
            }
        }
    }

    loadFile.close();
    cout << "[FileManager] Kartu dimuat.\n";
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

        if      (key == "CURRENT_BALANCE") outBalance = stod(val);
        else if (key == "LAST_WIN_AMOUNT") outLastWin = stod(val);
    }

    loadFile.close();
    cout << "[FileManager] Currency dimuat. Balance: " << outBalance << "\n";
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

        if      (key == "CURRENT_BET")      outBet        = stod(val);
        else if (key == "DIFFICULTY_LEVEL") outDifficulty = stoi(val);
    }

    loadFile.close();
    cout << "[FileManager] Game data dimuat.\n";
}

bool FileManager::fileExists() {
    string path = saveDirectory + fileName;
    ifstream f(path);
    return f.good();
}

void FileManager::logEvent(const string& eventDesc) {
    string path = saveDirectory + "event_log.txt";
    ofstream logFile(path, ios::app);
    if (!logFile.is_open()) return;
    logFile << "[" << getCurrentTimestamp() << "] " << eventDesc << "\n";
    logFile.close();
}

bool FileManager::validateFile() {
    string path = saveDirectory + fileName;
    ifstream f(path);

    if (!f.is_open()) {
        cout << "[FileManager] Validasi GAGAL: file tidak ditemukan.\n";
        return false;
    }

    f.seekg(0, ios::end);
    bool empty = (f.tellg() == 0);
    f.close();

    if (empty) {
        cout << "[FileManager] Validasi GAGAL: file kosong.\n";
        return false;
    }

    cout << "[FileManager] Validasi OK.\n";
    return true;
}
