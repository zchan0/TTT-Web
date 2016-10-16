#include <iostream>
#include "Player.h"
#include "Board.h"

#define SUMTABLESIZE DIMENSION * 2 + 2	// each row, col, diagonal and antidiagonal

Player::Player()
{
	name 	 = "";
	marker 	 = "";
	number 	 = 0;
}

//Player::~Player()
//{
 //	delete sumTable;
//}

Player::Player(const std::string n, const std::string m, const int num) 
{
	name     = n;
	marker   = m;
	number 	 = num;
	reset();
}

// This algorithm (what the following two functions do) credits to
// https://www.glassdoor.com/Interview/How-would-you-determine-if-someone-has-won-a-game-of-tic-tac-toe-on-a-board-of-any-size-QTN_1104.htm
bool Player::hasWon() const
{
	for (int i = 0; i < SUMTABLESIZE; ++i) {	
		if (sumTable[i] == DIMENSION) {
			return true;
		}
	}
	return false;
}

bool Player::isReady() const
{
	return number != 0;
}

void Player::setSelection(int row, int col)
{
	// add 1 to this row and col
	++sumTable[row];
	++sumTable[col + DIMENSION];
	// if (row, col) locates in diagonal or antidiagonal, add 1
	if (row == col) {
		sumTable[DIMENSION * 2] += 1; 
	} else if (row + col == DIMENSION - 1) {
		sumTable[DIMENSION * 2 + 1] += 1;
	}
}

void Player::reset()
{
	sumTable = new unsigned char[SUMTABLESIZE];

	for (int i = 0; i < SUMTABLESIZE; ++i) {	
		sumTable[i] = 0;
	}	
}

const std::string Player::getName() const
{
	return name;
}

const std::string Player::getMarker() const
{
	return marker;
}

int Player::getNumber() const
{
	return number;
}
