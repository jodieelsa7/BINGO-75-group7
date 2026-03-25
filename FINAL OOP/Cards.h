#include <vector>
#include <iostream>
using namespace std;

class Cards
{
private:
	int grid[5][5];
	bool markedPositions[5][5];

public:
	//Constructor
	Cards();

	//Destructor
	~Cards();

	//Getter
	int getCard();

	//Setter
	void setCard();

	//Function Members
	void generateCard();
	bool markNumber();
	bool checkPatters();
	string displayCards();

};

