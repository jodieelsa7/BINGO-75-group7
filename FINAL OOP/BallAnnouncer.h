#pragma once
#include <iostream>
#include <vector>
#include <random> //i used include algorithm, thinking i need it, but the code works fine without it so im just writing this just in case
#include <string>
using namespace std;


class BallAnnouncer
{
private:
	vector<int> numbers;
	size_t index;
	mt19937 rng; // Shuffles the numbers. As seen from: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution.html
	char getLetter(int n);
	bool hasNext();

	string callNext() {
		if (!hasNext())
			return "No more numbers.";

		int n = numbers[index++]; //move onto the next index
		char letter = getLetter(n); //get the letter corresponding the number they got
		return string(1, letter) + "-" + to_string(n); //honestly its just there to make it look nicer, like B-13 and stuff
	}
	friend BallAnnouncer(); //https://www.geeksforgeeks.org/cpp/friend-class-function-cpp/  to access the private thing
public:
	//CONSTRUCTORS
	BallAnnouncer();


};

 
};

