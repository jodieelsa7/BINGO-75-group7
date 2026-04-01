#include "Cards.h"

Cards::Cards() {
    generateCard();
}

int Cards::getGridValue(int row, int col) {
    return grid[row][col];
}

bool Cards::getMarkedStatus(int row, int col) { //to see if number in the position is marked or not
    return markedPositions[row][col];
}

void Cards::generateCard() {
    int numb = 0;
    vector<int> vUsedNumb;
    srand(unsigned(time(NULL)));

    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            bool isDuplicate;
            if (c == 0) {
                do {
                    isDuplicate = false; 
                    numb = (rand() % 15) + 1; // 1 - 15
                    for (int i = 0; i < vUsedNumb.size(); i++) {
                        if (vUsedNumb[i] == numb) {
                            isDuplicate = true;
                            break;
                        }
                    }
                } while (isDuplicate);
            }
            else if (c == 1) {
                do {
                    isDuplicate = false;
                    numb = (rand() % 15) + 16; // 16 - 30
                    for (int i = 0; i < vUsedNumb.size(); i++) {
                        if (vUsedNumb[i] == numb) {
                            isDuplicate = true;
                            break;
                        }
                    }
                } while (isDuplicate);
            }
            else if (c == 2) {
                if (r == 2) {
                    grid[r][c] = 0; // 0 = FREE
                    markedPositions[r][c] = true; // automatically mark it , since it's free
                    continue; // skip the rest of the loop for this specific cell
                }
                else {
                    do {
                        isDuplicate = false;
                        numb = (rand() % 15) + 31; // 31 - 45
                        for (int i = 0; i < vUsedNumb.size(); i++) {
                            if (vUsedNumb[i] == numb) {
                                isDuplicate = true;
                                break;
                            }
                        }
                    } while (isDuplicate);
                }
            }
            else if (c == 3) {
                do {
                    isDuplicate = false;
                    numb = (rand() % 15) + 46; // 46 - 60
                    for (int i = 0; i < vUsedNumb.size(); i++) {
                        if (vUsedNumb[i] == numb) {
                            isDuplicate = true;
                            break;
                        }
                    }
                } while (isDuplicate);
            }
            else { // c == 4
                do {
                    isDuplicate = false;
                    numb = (rand() % 15) + 61; // 61 - 75
                    for (int i = 0; i < vUsedNumb.size(); i++) {
                        if (vUsedNumb[i] == numb) {
                            isDuplicate = true;
                            break;
                        }
                    }
                } while (isDuplicate);
            }

            // save the number to the grid
            grid[r][c] = numb;
            // only set to false if it's NOT the center square
            if (!(r == 2 && c == 2)) {
                markedPositions[r][c] = false;
                vUsedNumb.push_back(numb);
            }
        }
    }
}

bool Cards::markNumber(int pulledNum) {
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (r == 2 && c == 2) {
                continue;
            }
            else if (grid[r][c] == pulledNum) {
                markedPositions[r][c] = true;
                return true;
            }
        }
    }
    return false;
}

bool Cards::checkPatterns() {
    //horizontal
    for (int r = 0; r < 5; r++) {
        int totalMarked = 0; // so it resets on every row
        for (int c = 0; c < 5; c++) {
            if (markedPositions[r][c] == true){
                totalMarked++;
            }
        }
        if (totalMarked == 5) {
            return true;
        }
    }

    //vertical
    for (int c = 0; c < 5; c++) {
        int totalMarked = 0; // so it resets on every collumn 
        for (int r = 0; r < 5; r++) {
            if (markedPositions[r][c] == true) {
                totalMarked++;
            }
        }
        if (totalMarked == 5) {
            return true;
        }
    }

    //diagonal (top left to bottom right)
    int diaMarked = 0;
    for (int i = 0; i < 5; i++) {
        if (markedPositions[i][i] == true) {
            diaMarked++;
        }
    }

    if (diaMarked == 5) {
        return true;
    }
    else {
        diaMarked = 0; // resets
    }

    //diagonal (top right to bottom left)
    for (int i = 0; i < 5; i++) {
        if (markedPositions[i][4 - i] == true) {
            diaMarked++;
        }
    }

    if (diaMarked == 5) {
        return true;
    }
    else {
        diaMarked = 0;
    }

    // four corners
    if ((markedPositions[0][0] && markedPositions[0][4] && markedPositions[4][0] && markedPositions[4][4]) == true) {
        return true;
    }

    //blackout
    int unmarked = 0;
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (markedPositions[r][c] == false) {
                unmarked ++;
            }
        }
    }

    if (unmarked == 0) {
        return true;
    }

    return false;
}

void Cards::displayCards() {
    cout << "========================\n"
         << YELLOW << "  B    I    N    G    O  \n" << RESETCOLOR
         << "------------------------\n";
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            string num = to_string(grid[r][c]);
            int width = 8;
            int padding = (width - num.length())/2;
            if (r == 2 && c == 2) {
                cout << "|" << RED << "" << setw(padding) << "FREE" << RESETCOLOR; //since setw() only applies to whatever that is exactly after itself, so RED should be before the setw(). i also add an empty string before the setw() so it wouldn't accidentally readh the "red" that is still on buffer
            }
            else if (markedPositions[r][c] == true) {
                if (c == 0 || c == 1 || c == 2 || c == 3) {
                    cout << "|" << RED << "" << setw(padding) << grid[r][c] << RESETCOLOR;
                }
                else { // if c == 4
                    cout << "|" << RED << "" << setw(padding) << grid[r][c] << RESETCOLOR << "|\n";
                } 
            }
            else { //number is not marked
                if (c == 0 || c == 1 || c == 2 || c == 3) {
                    cout << "|" << setw(padding) << grid[r][c];
                }
                else { // if c == 4
                    cout << "|" << setw(padding) << grid[r][c] << "|\n";
                }

            }
        }
    }
}
