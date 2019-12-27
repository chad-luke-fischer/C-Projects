#include "Bag.h"
#include "Board.h"
#include "ConsolePrinter.h"
#include "Dictionary.h"
#include "Exceptions.h"
#include "Move.h"
#include "Player.h"
#include "rang.h"
#include "Square.h"
#include "Tile.h"

#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		//error
	}

	ifstream ifile(argv[1]);

	int handSize;
	uint32_t seed;
	string board;
	string tiles;
	string dict;
	string in;

	while(getline(ifile, in))
	{
		stringstream stream(in);
		char temp;
		stream >> temp;
		if(temp == 'H')
		{
			while(temp != ':')
			{
				stream >> temp;
			}
			stream >> handSize;
		}
		else if(temp == 'T')
		{
			while(temp != ':')
			{
				stream >> temp;
			}
			stream >> tiles;
		}
		else if(temp == 'D')
		{
			while(temp != ':')
			{
				stream >> temp;
			}
			stream >> dict;
		}
		else if(temp == 'B')
		{
			while(temp != ':')
			{
				stream >> temp;
			}
			stream >> board;
		}
		else if(temp == 'S')
		{
			while(temp != ':')
			{
				stream >> temp;
			}
			stream >> seed;
		}
	}

	Dictionary diction(dict);
	//cout << diction.isLegalWord("xyz");
	Board board1(board);
	ConsolePrinter::printBoard(board1);

	size_t numPlayers;

	cout << "Enter number of players (1-8)" << endl;
	cin >> numPlayers;
	while(numPlayers > 8 || numPlayers <1)
	{
		cout << "Enter number of players (1-8)" << endl;
		cin >> numPlayers;
	}
	vector<Player*> players;

	for(size_t i = 0; i < numPlayers; i++)
	{
		string name;
		cout << "Enter player name." << endl;
		cin >> name;
		Player* playa = new Player(name, handSize);
		players.push_back(playa);
	}
	Bag bag(tiles, seed);
	cin.ignore();

	for(size_t i = 0; i< numPlayers; i++)
	{
		vector<Tile*> tilesToAdd = bag.drawTiles(handSize);
		players[i]->addTiles(tilesToAdd);
	}

	
	bool isPlaying = true;
	bool firstMove = true;
	do //game loop
	{
		//for(size_t i = 0; i < numPlayers; i++)
		//{	
			//ConsolePrinter::printHand(*(players[i]));
		//}
		for(size_t i = 0; i < numPlayers; i++)
		{	
			bool legalMove = true;
			do
			{
				std::string moveString;
				ConsolePrinter::printHand(*(players[i]));
				cout << "Enter Move for " << players[i]->getName() << endl;
				getline(cin, moveString);
				Move* playerMove;
				//error? if parsemove has bad input
				playerMove = Move::parseMove(moveString, *players[i]);
				try
				{
					playerMove->execute(board1, bag, diction); //SEG_FAULT
					legalMove = true;
				}
				catch(BadMoveException b) 
				{
					cout << b.getMessage();

					legalMove = false;
				}
				ConsolePrinter::printBoard(board1);

			}while(legalMove == false);
		} 
	}while(isPlaying);
	



	//cout << players[1]->hasTiles("pilesxx", true);

	//cout << "Handsize: " << handSize << endl;
	//cout << "Tiles: " << tiles << endl;
	//cout << "Dictionary: " <<  dict << endl;
	//cout << "Board: " << board << endl;
	//cout << "Seed: " << seed << endl;
}


