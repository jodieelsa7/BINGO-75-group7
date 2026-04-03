#ifndef CURRENCY_H
#define CURRENCY_H

using namespace std;

class Currency
{
private:
    double currentBalance;
    double lastWinAmount;

public:
    Currency(double start);
    void subtractLoss(double amt);
    void addWins(double amt);
    double getBalance();
};

#endif CURRENCY_H
