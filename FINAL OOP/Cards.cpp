/*
Student Name: Jodie Elsa Soenarto
Student ID: 251103120132
Course: FITS1201 – Object Oriented Programming
Assignment: Final Project – Bingo-75 Game
Academic Integrity Declaration:
I declare that this work is my own and that I have not copied
code from other students, websites, or online repositories
without proper acknowledgement.
*/

#include "Cards.h"

Cards::Cards() {
    generateCard();
}

// we MIGHT no need these getters
//int Cards::getGridValue(int row, int col) {
//    return grid[row][col];
//}
//
//bool Cards::getMarkedStatus(int row, int col) { //to see if number in the position is marked or not
//    return markedPositions[row][col];
//}

void Cards::generateCard() {
    int numb = 0;
    vector<int> vUsedNumb;

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

int Cards::checkPatterns() {

    //blackout
    int unmarked = 0;
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (markedPositions[r][c] == false) {
                unmarked++;
            }
        }
    }
	if (unmarked == 0) {
        return 5; // blackout bingo
	}

    // four corners
    if ((markedPositions[0][0] && markedPositions[0][4] && markedPositions[4][0] && markedPositions[4][4]) == true) {
		return 4; // four corners bingo
    }

    //diagonal (top left to bottom right)
    int diaMarked = 0;
    for (int i = 0; i < 5; i++) {
        if (markedPositions[i][i] == true) {
            diaMarked++;
        }
    }

    if (diaMarked == 5) {
		return 3; // diagonal bingo
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
		return 3; // diagonal bingo
    }
    else {
        diaMarked = 0;
    }

    //horizontal
    for (int r = 0; r < 5; r++) {
        int totalMarked = 0; // so it resets on every row
        for (int c = 0; c < 5; c++) {
            if (markedPositions[r][c] == true){
                totalMarked++;
            }
        }
        if (totalMarked == 5) {
			return 2; // horizontal bingo
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
            return 1; // vertical bingo
        }
    }

    return 0; // no bingo
}

void Cards::displayCards() {
	cout << "=============================================\n"
		<< YELLOW << "      B       I       N       G       O      \n" << RESETCOLOR
		<< "---------------------------------------------\n";

	for (int r = 0; r < 5; r++) {
		for (int c = 0; c < 5; c++) {
            string content;
			if (r == 2 && c == 2) {
				content = "FREE";
			}
			else {
				content = to_string(grid[r][c]);
			}

			// calculating the padding logic
			int cellWidth = 8;
			int totalSpaces = cellWidth - (int)content.length();
			int leftPad = totalSpaces / 2;
			int rightPad = totalSpaces - leftPad;

			//THE DISPLAYING
			cout << "|";

			if (leftPad > 0) cout << setw(leftPad) << ""; // apply left padding using setw on an empty string

			if (markedPositions[r][c] == true) {
				cout << RED << content << RESETCOLOR;
			}
			else {
				cout << content;
			}

			if (rightPad > 0) cout << setw(rightPad) << ""; // apply right padding using setw on an empty string

			if (c == 4) {
				cout << "|\n"; // right border
				cout << "---------------------------------------------\n";
			}
		}
	}
}


void Cards::loadCardState(int loadedGrid[5][5], bool loadedMarked[5][5]) {
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            grid[r][c] = loadedGrid[r][c];
            markedPositions[r][c] = loadedMarked[r][c];
        }
    }
}

void Cards::getCardState(int outGrid[5][5], bool outMarked[5][5]) {
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            outGrid[r][c] = grid[r][c];
            outMarked[r][c] = markedPositions[r][c];
        }
    }
}
