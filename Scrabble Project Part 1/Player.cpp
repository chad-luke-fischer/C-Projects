#include "Player.h"
#include <algorithm>
#include <string>
#include <vector>
#include "Exceptions.h"
#include <iostream>

/* Constructor giving the player the given name, and setting their points to 0.
	   Does not give the player any tiles.
	*/
	Player::Player (std::string const & name, size_t maxTiles)
	{
		PlayerName = name;
		points = 0;
		mTiles = maxTiles;
	}

	/* Destructor for a player. Deletes all the tiles the player still has. */
	Player::~Player ()
	{
		while(!tiles.empty())
		{
			tiles.erase(tiles.end());
		}

	}
	

	/* Returns the set of tiles the player currently holds. */
	std::set<Tile*> Player::getHandTiles() const
	{
		std::set<Tile*> tileset;
		for(int i = 0; i < tiles.size(); i++)
		{
			tileset.insert(tiles[i]);
		}
		return tileset;
	}

	/* Reads a move string and confirms that the player has the tiles necessary to
	   execute this move.

	   The move string is case-insensitive.

	   The boolean resolveBlanks states whether this is a PLACE or EXCHANGE move.
	   If resolveBlanks is true, then when the string contains a '?',
	   the next letter is interpreted as the letter to use the blank as.

	   By definition, if this function returns true, then takeTiles() would
	   succeed.
	 */

	bool Player::hasTiles(std::string const & move, bool resolveBlanks) 
	{
		std::string tempMove = move;
		transform(tempMove.begin(),tempMove.end(), tempMove.begin(), ::tolower);

		//return true;
		bool hasit = true;
		bool letterIsFound = false;
		std::string letters = "";
		for(unsigned int i = 0; i < tiles.size();i++)
		{
			letters += tiles[i]->getLetter();
		}
		unsigned int movelen = tempMove.size();
		unsigned int strlength = letters.size();

		for(unsigned int i = 0; i < movelen;i++)
		{
			letterIsFound = false;
			if(resolveBlanks && tempMove[i] == '?') //if resolveblanks
			{
				i++;
				for(unsigned int j = 0; j < strlength;j++)
				{
					if(tempMove[j] == '?')
					{
						letters.erase(j,1);
						letterIsFound = true;
						strlength--;
						break;
					}
				}
			}
			else //no resolveblanks
			{
				for(unsigned int j = 0; j < strlength; j++)
				{
					if(tempMove[i]==letters[j])
					{
						letters.erase(j,1);
						letterIsFound = true;
						strlength--;
						break;
					}
				}
			}
			if(!letterIsFound){return false;}
		}
		return hasit;
	}


	/* Reads a move string, finds the corresponding tiles in the player's hand, and
	   removes and returns those tiles in the order they appear in the move string.

	   The move string is case-insensitive.

	   The boolean resolveBlanks states whether this is a PLACE or EXCHANGE move.
	   If resolveBlanks is true, then when the string contains a '?',
	   the next letter is interpreted as the letter to use the blank as,
	   and the "use" field of the tile is set accordingly.

	   The move string is assumed to have correct syntax.
	*/
	std::vector<Tile*> Player::takeTiles (std::string const & move, bool resolveBlanks)
	{
		std::string tempMove = move;
		transform(tempMove.begin(),tempMove.end(), tempMove.begin(), ::tolower);


		std::vector<Tile*> newTiles;
		int vecSize = tiles.size();
		
		for (int i=0; i < move.size(); i++)
		{
			if(move[i] == '?' && resolveBlanks)
			{
				i++;
				for(int j=0; j < vecSize;j++)
				{
					if(tiles[j]->getLetter() == '?')
					{
						tiles[j]->useAs(tempMove[i]);
						newTiles.push_back(tiles[j]);
						tiles.erase(tiles.begin()+j);
						vecSize--;
					}
				}
			}
			else
			{
				for(int j = 0; j < vecSize; j++)
				{
					if(tiles[j]->getLetter()==tempMove[i])
					{
						newTiles.push_back(tiles[j]);
						tiles.erase(tiles.begin()+j);
						vecSize--;
					}
				}
			}
		}
		return newTiles;
	}

	// Adds all the tiles in the vector to the player's hand.
	void Player::addTiles (std::vector<Tile*> const & tilesToAdd)
	{

		for(int size = 0; size < tilesToAdd.size(); size++)
		{
			tiles.push_back(tilesToAdd[size]);
		}

	}

	size_t Player::getMaxTiles() const
	{
		return mTiles;
	}