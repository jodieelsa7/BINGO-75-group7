#include "Players.h"
#include "BallAnnouncer.h"
#include "Display.h"
#include "Timer.h"
using namespace std;

class GameManager
{
private:
	Players activePlayer;
	BallAnnouncer announceNumber;
	Display menu;
	Timer numberTimer;

public: 
	void startGame();
	void mainLoop();
	void processTurn();

};

