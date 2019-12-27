#include "Move.h"
#include "Board.h"
#include "fstream"
#include <string>
#include <iostream>

using namespace std;

/*
 * Move.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

/* The Move class family encodes a move made by one player, including its type
   (PASS, EXCHANGE, PLACE), the tiles used (and use for blanks),
   start square, and direction (if needed).
   Call Move::parseMove() to turn an entered string into its subclass of
   Move, then call apply() on that returned move to have it execute.*/



// Represents a pass move, where the player takes no action

	Move * Move::parseMove(std::string moveString, Player &p)
	{
		Move* ret;
		stringstream stream(moveString);
		string moveType;
		stream >> moveType; 
		if(moveType == "PASS" || moveType == "pass")
		{
			ret = new PassMove(&p);
		}
		else if(moveType == "EXCHANGE" || moveType == "exchange")
		{
			string exchangeTiles;
			stream >> exchangeTiles;
			ret = new ExchangeMove(exchangeTiles, &p);
		}
		else if(moveType == "PLACE" || moveType == "place")
		{
			bool horiz;
			char dir;
			size_t row,col;
			string move;
			stream >> dir;
			if(dir == '-'){horiz = true;}
			else if(dir == '|'){horiz = false;}
			stream >> row >> col >> move;
			ret = new PlaceMove(col, row, horiz, move, &p);
		}
		return ret;
	}

	Move::Move(Player* p)
	{
		_player = p;
	}

	Move::~Move(){delete this;}

	/* Constructs a pass move. */
	PassMove::PassMove(Player * player):Move(player)
    {
        
    }

	

	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/
	void PassMove::execute(Board & board, Bag & bag, Dictionary & dictionary)
    {
		

    }

	//Add more public/protected/private functions/variables here.



// represents an exchange move, were a player replaces certain tiles

	/* Creates an EXCHANGE move, exchanging the tiles listed in the
	   string (formatted according to the EXCHANGE command description)
	   with new tiles from the bag.
	   */
	ExchangeMove::ExchangeMove(std::string tileString, Player * p):Move(p)
    {
        _tileString = tileString;

    }

	/* Returns true iff the move is an EXCHANGE move */

	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/
	void ExchangeMove::execute(Board & board, Bag & bag, Dictionary & dictionary)
    {
        if(!_player->hasTiles(_tileString, true))
        {
            throw BadMoveException("ERROR: Player doesn't have tiles");
        }
		//put tiles back in bag
        _player->takeTiles(_tileString, true);
        _player->addTiles(bag.drawTiles(_tileString.size()));

        
    }

	//Add more public/protected/private functions/variables here.

// represents a place move, where a player places one or more tiles onto the board.

	/* Creates a PLACE move, starting at row y, column x, placing the tiles
	   described by the string tileString. If "horizontal" is true, then the tiles
	   are placed horizontally, otherwise vertically.
	   Coordinates start with 1.
	   The string m is in the format described in HW4; in particular, a '?'
	   must be followed by the letter it is to be used as.
	*/
	PlaceMove::PlaceMove (size_t x, size_t y, bool horizontal, std::string tileString, Player * p):Move(p)
    {
        _x = x;
		_y = y;
		_horizontal = horizontal;
		_tileString = tileString;
		_tileVectors = _player->takeTiles(_tileString, true);
    }


	/* Returns the vector of tiles associated with a PLACE/EXCHANGE move.
	   Return value could be arbitrary for PASS moves. */
	std::vector<Tile*> const & PlaceMove::tileVector () const
    {
		// vector<Tile*> ret;
		// if(_player->hasTiles(_tileString, true))
		// {
		// 	ret = _player->takeTiles(_tileString, true);
		// }
		// return ret;
		return _tileVectors;

    }

	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/
	void PlaceMove::execute(Board & board, Bag & bag, Dictionary & dictionary)
    {
		size_t strSize = _tileString.size();
		size_t end;
		bool firstMove = true;
		bool connected = false;
		bool startsOnStart = false;

		if(!(board.getSquare(board._starty,board._startx)->isOccupied()))//check if part of first word is on start
		{
			for(int i = 0; i < _tileString.size(); i++)
			{
				if(board.getSquare(_x+i, _y)->isStart())
				{
					startsOnStart = true;
				}
				else if(board.getSquare(_x, _y+i)->isStart())
				{
					startsOnStart = true;
				}
			}
		}
		if(!startsOnStart)
		{
			_player->addTiles(_tileVectors);
			throw BadMoveException("ERROR: doesnt start on start pos");
		}


		if(_horizontal)
		{
			end = _y + strSize-1;
		}
		else
		{
			end = _x + strSize-1;
		}
		for(int i = 0; i < _tileString.size(); i++)
		{
			if(_tileString[i]=='?')
			{
				_tileString.erase(i, 1);
			}
		}
		if(!dictionary.isLegalWord(_tileString))
		{
			_player->addTiles(_tileVectors);
			throw BadMoveException("ERROR: Illegal word");
		}

		Square* occupied;
		string str;
		
		//must be adj square if not firstmove
		//cannot be placed on placed tile
		//firstmove must be on start tile
		//Each maximal sequence (meaning that on both ends,
		//	it is bordered by an empty square or the end of the board)
		
		if(end < board.getRows())
		{
			vector<Tile*> _vec = this->tileVector();
			for(int i = 0; i < _vec.size(); i++)
			{
				Square* placeSquare;
				if(_horizontal)
				{
					placeSquare = board.getSquare(_x + i, _y);
				}
				else
				{
					placeSquare = board.getSquare(_x, _y + i);
				}
				placeSquare->placeTile(_vec[i]);
			}
			_player->addTiles(bag.drawTiles(_vec.size()));
		}
    }

	
