#include "../model/Player.h"
#include "../model/Board.h"

namespace patch
{
    template <typename T> std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

class TTTController
{
	public:
		int  determineWinner();
		std::string getGameDisplay();
		std::string getGameDisplay(bool isJson);
		std::string getAllSavedPlayers();

		void startNewGame();
		void createPlayer(std::string playerJsonStr);
		void createPlayer(std::string name, std::string marker, int playerNum = 1);
		bool setSelection(std::string gameJsonStr);
		bool setSelection(int row, int col, int currentPlayer);	
		
	private:
		std::string getMarkerByPlayerNum(int playerNum) const;
		Player A, B;
};
