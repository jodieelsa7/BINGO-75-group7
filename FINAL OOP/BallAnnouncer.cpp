#include "BallAnnouncer.h"

BallAnnouncer::BallAnnouncer(){
	index(0);
	BallAnnouncer.rng(random_device{}());
	for (int i = 1; i <= 75; ++i) { //fill the vector with 1-75
		numbers.push_back(i);

		shuffle(numbers.begin(), numbers.end(), rng); //shuffle the order
	}


char getLetter (int n) 
{ //convert the number into letter
	if (n <= 15 && n >= 0) return 'B';
	else if (n <= 30 && n >= 16) return 'I';
	else if (n <= 45 && n >= 31) return 'N';
	else if (n <= 60 && n >= 46) return 'G';
	else if (n <= 75 && n >= 61) return 'O';
	else {
		cout << "letter failed to get";
	}
}

bool hasNext() {
	return index < numbers.size(); //check if there's any number left
}

string callNext() {
	if (!hasNext())
		return "No more numbers.";

	int n = numbers[index++]; //move onto the next index
	char letter = getLetter(n); //get the letter corresponding the number they got
	return string(1, letter) + "-" + to_string(n); //honestly its just there to make it look nicer, like B-13 and stuff
}