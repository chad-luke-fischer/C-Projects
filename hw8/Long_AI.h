#include "Super_AI"
#include "Move.h"
#include "Dictionary.h"
#include "Exceptions.h"
#include <vector>
#include <string>

class Long_AI : public Player
{
public:
	Long_AI();
	~Long_AI();
	string getName();

	Move getMove(const Board& board, const Player& player, std::map<char, int> initialTilecount);

	//vertical and hz helper functions



private:
	Dictionary* dict;
	vector<vector<string> > moves;
	vector<int> scores;


};
