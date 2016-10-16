#include "../model/Player.h"
#include "../model/Board.h"

class TTTController
{
	public:
		int  determineWinner();
		void startNewGame();
		bool setSelection(int row, int col, int currentPlayer);	
		void createPlayer(std::string name, std::string marker, int playerNum = 1);
		std::string getGameDisplay();
	private:
		Player A, B;
};
