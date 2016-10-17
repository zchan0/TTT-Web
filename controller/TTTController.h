#include "../model/Player.h"
#include "../model/Board.h"

class TTTController
{
	public:
		int  determineWinner();
		std::string getGameDisplay();
		std::string getGameDisplay(bool isJson);
		std::string getAllSavedPlayers();

		void startNewGame();
		void createPlayer(std::string playerJsonObject);
		void createPlayer(std::string name, std::string marker, int playerNum = 1);
		bool setSelection(std::string gameJsonObject);
		bool setSelection(int row, int col, int currentPlayer);	
		
	private:
		Player A, B;
};
