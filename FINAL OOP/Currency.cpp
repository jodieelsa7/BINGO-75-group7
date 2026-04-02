#include "Currency.h"

Currency::Currency(double start = 100.0) {
  currentBalance(start);
  lastWinAmount(0);
  }

void Currency::subtractLoss(int amt) {
    currentBalance -= amt;
}

void Currency::addWins(int amt) {
    lastWinAmount = amt;
    currentBalance += amt;
}

double Currency::getBalance() {
    return currentBalance;
}
