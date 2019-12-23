#include "Super_AI.h"

#include <iostream>


Super_AI::Super_AI(std::string name, size_t maxTiles, Board* board, Dictionary* dict) :Player(name, maxTiles)
{
	this->board = board;
	this->dict = dict;
}

Super_AI::~Super_AI()
{

}

void Super_AI::anchor_down()// marks tiles adjacent to occupied tiles as anchors
{							// anchors represent connections to the given board where AI can make moves
	poss_moves.clear();

	int rows = board->getRows();
	int cols = board->getColumns();
	bool found = false;		

	for(int i = 1; i <= rows;i++)
	{
		for(int j = 1; j <= cols; j++)
		{
			found = false;	
			if(!board->getSquareM(i,j)->isOccupied())  
			{
				if(i-1 > 0)
				{
					if(board->getSquareM(i-1,j)->isOccupied())
					{
						board->getSquareM(i,j)->setAnchor(true);
						found = true;
					}
				}
				if(i+1 <= rows)
				{
					if(board->getSquareM(i+1,j)->isOccupied())
					{
						board->getSquareM(i,j)->setAnchor(true);
						found = true;
					}
				}
				if(j-1 > 0)
				{
					if(board->getSquareM(i,j-1)->isOccupied())
					{
						board->getSquareM(i,j)->setAnchor(true);
						found = true;
					}
				}
				if(j+1 <= cols)
				{
					if(board->getSquareM(i,j+1)->isOccupied())
					{
						board->getSquareM(i,j)->setAnchor(true);
						found = true;
					}
				}
			}
			else
			{
				board->getSquareM(i,j)->setAnchor(false);
			}
			if(found == false)
			{
				board->getSquareM(i,j)->setAnchor(false);
			}
		}
	}
	return;
}

void Super_AI::left(std::string partial_word, TrieNode* node, bool dir, int row, int col)
{
	if(row < 0 || row > (int)board->getRows() || col < 0 || col > (int)board->getColumns())
	{
		return;
	}

	std::vector<Tile*> removed_tiles;

	right(partial_word, node, dir, row, col, true); //change from true?

	for(int i = 0; i < 26;i++)
	{
		if(node->children[i] != NULL)
		{
			std::string letter = "";
			letter += node->c;
			if(this->hasTiles(letter,false))
			{
				removed_tiles = this->takeTiles(letter,false);
				partial_word += letter;
				left(partial_word, node, dir, row, col);
				this->addTiles(removed_tiles);
			}
		}
	}


}

void Super_AI::right(std::string partial_word, TrieNode* node, bool dir, int row, int col, bool anchor_covered)
{

	if(row < 0 || row > (int)board->getRows() || col < 0 || col > (int)board->getColumns())
	{
		if(legal(partial_word, row, col, true))
		{
			poss_moves.push_back(make_pair(partial_word, board->getSquare(row,col)));
		}
		return;
	}

	std::vector<Tile*> removed_tiles;

	if(!board->getSquare(row, col)->isOccupied())
	{
		if(node->inSet)
		{
			if(legal(partial_word,row,col,true))
			{
				poss_moves.push_back(make_pair(partial_word, board->getSquare(row,col)));
			}
			for(int i = 0; i < 26; i++)
			{
				if(node->children[i] != NULL)
				{
					std::string letter = "";
					letter += node->c;
					if(this->hasTiles(letter, false))
					{
						removed_tiles = this->takeTiles(letter,false);
						partial_word += letter;
						right(partial_word, node, true, row, col+1, true);
						this->addTiles(removed_tiles);
					}
				}
			}
		}
		else
		{
			char c = board->getSquare(row,col)->getLetter();
			c = tolower(c);
			if(node->children[c - 'a'] != NULL)
			{
				partial_word += c;
				right(partial_word, node->children[c - 'a'], true, row, col+1, true);
			}

		}
	}
}

// std::string Super_AI::getScoreMove()
// {
// 	// string hand;
// 	// set<Tile*> tile_set = this->getHandTiles();
// 	// for(set<Tile*>::iterator it = tile_set.begin(); it != tile_set.end();++it)
// 	// {
// 	// 	hand+=(*it)->getLetter();
// 	// }

// 	// //MAKE CALLS TO FILL UP POSS_MOVES

// 	// if(poss_moves.empty())
// 	// {
// 	// 	return "PASS";
// 	// }
// 	// else
// 	// {
// 	// 	int max = -1;
// 	// 	int temp_max = 0;
// 	// 	int score_word;

// 	// 	for(int i = 0; i < poss_moves.size();i++)
// 	// 	{
// 	// 		PlaceMove* move = new PlaceMove(x,y,dir,poss_moves[i].first,this); //creates move to pass into getPlacemoveResults
// 	// 		std::vector<std::pair<std::string, unsigned int> > words_formed = board->getPlaceMoveResults(*move);
// 	// 		for(int j = 0; j < words_formed; j++)
// 	// 		{
// 	// 			temp_max += words_formed[j].second;
// 	// 		}
// 	// 		if(temp_max > max)
// 	// 		{
// 	// 			max = temp_max;
// 	// 			score_word = poss_moves[i].first;
// 	// 		}
// 	// 		else temp_max = 0;
// 	// 	}

// 	 	//return score_word;
// 	// }
// }

// std::string Super_AI::getLongMove()
// {
	
// }



bool Super_AI::legal(std::string word, int x, int y, bool dir)
{
	PlaceMove* move = new PlaceMove(x,y,dir,word,this);
	std::vector<std::pair<std::string, unsigned int> > move_score = board->getPlaceMoveResults(*move);

	for(int i = 0; i < (int)move_score.size();i++)   // this is going thru number of words not each letter in string
	{
		if(!dict->isLegalWord(move_score[i].first))
		{
			delete move;
			return false;
		}
	}
	return true;

}

