#include <string>
#include <map>
#include <vector>

#include "Move.h"
#include "Dictionary.h"
#include "Board.h"
#include "Player.h"

class Super_AI: public Player
{
public:

	Super_AI(std::string name, size_t maxTiles, Board* board, Dictionary* dict);

	~Super_AI();

	void anchor_down(); // marks tiles adjacent to occupied tiles as anchor

	void left(std::string partial_word,TrieNode* node, bool dir, int row, int col);

	void right(std::string partial_word,TrieNode* node, bool dir, int row, int col, bool anchor_covered);

	std::string getScoreMove();

	std::string getLongMove();

	bool legal(std::string word, int x, int y, bool dir);
	



	Board* board;
	Dictionary* dict;
	std::vector<std::pair<std::string, Square*> > poss_moves;
};

