#include <iostream>
#include <string>
#include <sstream>

#include "TTTController.h"
#include "DataManager.h"
#include "../model/Json.h"

Board* Board::instance = NULL;	// Singleton
static const std::string playersFilename   = "players.txt";
static const std::string gameBoardFilename = "board.txt";

/**
 * Can create two players at most, any more calls will be ignored
 */	
void TTTController::createPlayer(std::string name, std::string marker, int playerNum)
{
	if (!A.isReady() && playerNum == 1) {
		A = Player(name, marker, playerNum);
	} else if (!B.isReady() && playerNum == 2) {
		B = Player(name, marker, playerNum);
	}
}

/**
 * format of playerJsonObject: {name:string, marker:string, playerNum:int}
 */
void TTTController::createPlayer(std::string playerJsonStr)
{
	JsonParser parser  = JsonParser(playerJsonStr);
	Json playerJson    = parser.parseJson();
  
  int playerNum = playerJson["playerNum"].intValue();
	std::string name   = playerJson["name"].stringValue();
	std::string marker = playerJson["marker"].stringValue();
	
	createPlayer(playerJson["name"].stringValue(), playerJson["marker"].stringValue(), playerJson["playerNum"].intValue());
	
	// persist new player
	DataManager &dataManager = DataManager::getInstance();
	dataManager.write(playersFilename, playerJsonStr);	
}

void TTTController::startNewGame()
{
	Board::getInstance() -> reset();
	A.reset();
	B.reset();

	// clear persist data
	// DataManager &dataManager = DataManager::getInstance();
	// dataManager.empty(playersFilename);
	// dataManager.empty(gameBoardFilename);
}

/**
 * @param  gameJsonObject {row:int, col:int, int: currentPlayer, string: marker }
 * @return                as below
 */
bool TTTController::setSelection(std::string gameJsonStr)
{
	JsonParser parser = JsonParser(gameJsonStr);
	Json gameJson = parser.parseJson();

	int row = gameJson["row"].intValue();
	int col = gameJson["col"].intValue();
	int num = gameJson["currentPlayer"].intValue();

	bool validSelection = setSelection(row - 1, col - 1, num);
	if (validSelection) {
		Json::object obj = gameJson.objectItems();
		obj["marker"] = Json(getMarkerByPlayerNum(num));
		Json json = Json(obj);
		std::string in;
		json.dump(in);
		DataManager &dataManager = DataManager::getInstance();
		dataManager.write(gameBoardFilename, in);
	}

	return validSelection;	
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
		// std::cout << "Game over. Player " << A.getName() << " won!" << std::endl;
		return 1;
	}
	if (B.hasWon()) {
		// std::cout << "Game over. Player " << B.getName() << " won!" << std::endl;
		return 2;
	}
	if (Board::getInstance() -> getAvailableSquares() == 0) {
		// std::cout << "Game over in a tie." << std::endl;
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
		std::string players, gameboard;
		int winner = determineWinner();
		DataManager &dataManager = 	DataManager::getInstance();
		dataManager.read(gameBoardFilename, gameboard);
		return "{\"gameBoard\": " + gameboard + "}";
	} else {
		return getGameDisplay();
	}
}

std::string TTTController::getGameDisplay()
{
	return Board::getInstance() -> getDisplayString(A.getMarker(), B.getMarker());
}

/**
 * {players : [{name:string, marker:string}, ...] }
 */
std::string TTTController::getAllSavedPlayers()
{
	DataManager& dataManager = DataManager::getInstance();
	std::string out;
	dataManager.read(playersFilename, out, DataManager::LASTTWO);
	return 	"{\"players\":" + out + "}";
}

std::string TTTController::getMarkerByPlayerNum(int playerNum) const
{
	switch(playerNum) {
		case 1:
		 return A.getMarker(); break;
		case 2: 
		 return B.getMarker(); break;
		default:
			return "-1"; break;
	}
}
