#include <iostream>

#include "TTTController.h"
#include "../model/Json.h"

Board* Board::instance = NULL;	// Singleton

/**
 * Can create two players at most, any more calls will be ignored
 */	
void TTTController::createPlayer(std::string name, std::string marker, int playerNum)
{
	if (!A.isReady()) {
		A = Player(name, marker, playerNum);
	} else if (!B.isReady()) {
		B = Player(name, marker, playerNum);
	}
}

/**
 * format of playerJsonObject: {name:string, marker:string, playerNum:int}
 */
void TTTController::createPlayer(std::string playerJsonStr)
{
	std::cout << playerJsonStr << std::endl;
	JsonParser parser  = JsonParser(playerJsonStr);
	Json playerJson    = parser.parseJson();

	createPlayer(playerJson["name"].stringValue(), playerJson["marker"].stringValue(), playerJson["playerNum"].intValue());
}

void TTTController::startNewGame()
{
	Board::getInstance() -> reset();
	A.reset();
	B.reset();
}

/**
 * @param  gameJsonObject {row:int, col:int, int: currentPlayer }
 * @return                as below
 */
bool TTTController::setSelection(std::string gameJsonStr)
{

}

/**
 * currentPlayer selected (row, col) square
 * @param  row           0 ~ Dimension - 1
 * @param  col           0 ~ Dimension - 1
 * @param  currentPlayer current player.number
 * @return               valid and available locations
 */
bool TTTController::setSelection(int row, int col, int currentPlayer)
{
	// check validaty of row, col and currentPlayer
	if (row < 0 || col < 0 ||
		row > DIMENSION - 1 || col > DIMENSION - 1) {
		std::cout << "Invalid location: row/col between 1 and " << DIMENSION << std::endl;
		return false;
	}

	if (currentPlayer != A.getNumber() && currentPlayer != B.getNumber()) {
		std::cout << "Invalid player number: currentPlayer should only be " << A.getNumber() << " or " << B.getNumber() << std::endl;
		return false;
	}
	
	if (Board::getInstance() -> setSelection(row, col, currentPlayer)) {
		if (currentPlayer == A.getNumber()) {		
			A.setSelection(row, col);
		} else if (currentPlayer == B.getNumber()) {
			B.setSelection(row, col);
		}
		return true;
	}

	return false;
}

/**
 * @return 0 - no winner
 *         1 - winner is player A
 *         2 - winner is player B
 *         3 - tie
 */
int TTTController::determineWinner()
{
	if (A.hasWon()) {
		std::cout << "Game over. Player " << A.getName() << " won!" << std::endl;
		return 1;
	}
	if (B.hasWon()) {
		std::cout << "Game over. Player " << B.getName() << " won!" << std::endl;
		return 2;
	}
	if (Board::getInstance() -> getAvailableSquares() == 0) {
		std::cout << "Game over in a tie." << std::endl;
		return 3;
	}
	return 0;
}

/**
 * @return        {gameBoard : [{row:int, col:int, marker:string}]
 */
std::string TTTController::getGameDisplay(bool isJson)
{
	if (isJson) {
		
	} else {
		getGameDisplay();
	}
}

std::string TTTController::getGameDisplay()
{
	return Board::getInstance() -> getDisplayString(A.getMarker(), B.getMarker());
}

std::string TTTController::getAllSavedPlayers()
{

}