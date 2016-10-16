#include <string>

class Player
{
	public:
		Player();
		//~Player();
		Player(const std::string n, const std::string m, const int num);
		bool hasWon() const;
		bool isReady() const;
		int getNumber() const;
		const std::string getName() const;
		const std::string getMarker() const;
		void setSelection(int row, int col);
		void reset();

	private:
		int number;
		std::string name;
		std::string marker;
		unsigned char* sumTable;	
};
