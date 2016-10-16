#include <iostream>
#include "Board.h"

Board::Board()
{
	squares  = new unsigned char[DIMENSION * DIMENSION];
	lastTurn = 0;
}

Board::~Board()
{
	delete squares;
}

Board* Board::getInstance()
{
	if (!instance) {
		instance = new Board();
	}
	return instance;
}

void Board::reset()
{
	lastTurn = 0;
	for (int i = 0; i < DIMENSION * DIMENSION; ++i) {
		squares[i] = 0;
	}
}

std::string Board::getDisplayString(const std::string markerA, const std::string markerB)
{
	std::string display = "\n";
	int playerNum = 0;
	for (int i = 0; i < DIMENSION * DIMENSION; ++i) {
		playerNum = squares[i]; 
		switch(playerNum) {
			case 1:	
				display.append(markerA + "\t");
				break;
			case 2:
				display.append(markerB + "\t");
				break;
			default:
				display.append("_\t");
				break;
		}
		if ((i + 1) % DIMENSION == 0) {
			display.append("\n\n");
		}
	}
	return display;
}

bool Board::setSelection(int row, int col, int playerNum)
{
	// check if it is right turn
	if (lastTurn != 0 && lastTurn == playerNum) {
		std::cout << "Be patient. It's another guy's turn." << std::endl;
		return false;
	}

	// if this square already has piece, it could not be selected.
	if (squares[row * DIMENSION + col] != 0) {
		std::cout << "This square already has a piece. Try another." << std::endl;
		return false;
	}

	lastTurn = playerNum;
	squares[row * DIMENSION + col] = playerNum;
	
	return true;
}

int Board::getAvailableSquares()
{
	int sum = 0;
	for (int i = 0; i < DIMENSION * DIMENSION; ++i) {
		if (squares[i] == 0) {
			++sum;
		}	
	}
	return sum;
}

