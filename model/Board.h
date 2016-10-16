#include <string>

#define DIMENSION 3

class Board
{
	public:
		static Board* getInstance();
		void reset();
		bool setSelection(int row, int col, int playerNum);
		int getAvailableSquares();
		std::string getDisplayString(const std::string markerA, const std::string markerB);
		~Board();
	
	private:
		Board();
		// Following two functions are for Singleton Pattern.
		Board(const Board&);
		Board& operator=(const Board&);

		int lastTurn;
		static Board* instance;
		unsigned char* squares;
};
