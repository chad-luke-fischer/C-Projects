#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <random>
#include <fstream>
#include "duck_duck_goose.h"


int main(int argc, char* argv[])
{
	GameData* gameData = new GameData();
	unsigned int seedvalue;//stores seed value from config
	int players, itID, currentID;//variables will respectively store number of players,
	//the id of the it player, and the current players ID


	if (argc < 3) 
	{
    	return 1;
   	}   
   	std::ofstream outputFile(argv[2]);
   	std::ifstream inputFile(argv[1]);

   	inputFile >> seedvalue;//read in seed val
   	srand(seedvalue);//set seed

   	inputFile >> players;//save players
   	inputFile >> itID;//save it players ID

   	gameData->itPlayerID = itID; //set it players ID to correct position in circular list

   	//loop will read in and push back each playerID to the games list
   	for(int i = 0; i < players; i++)
   	{
   		inputFile >> currentID;
   		gameData->playerList.push_back(currentID);
   	}

   	while(gameData->itPlayerID)
   	{
   		simulateDDGRound(gameData,outputFile);
   	}
   	inputFile.close();
   	outputFile.close();
   	delete gameData; 
}

void simulateDDGRound(GameData * gameData, std::ostream & output)
{
	int m = rand()%(4*(gameData->playerList.size()));
	int goosenum = m+1;
	int gooseID = gameData->playerList.get(goosenum);
	int duckID;

	for(int i = 0; i < m; i++)
	{
		duckID = gameData->playerList.get(i);
		output << duckID << " is a Duck." << std::endl;
	}
	output << gooseID << " is a Goose!" << std::endl;
	int itRand, gooseRand;
	itRand = rand() % 50;
	gooseRand = rand() % 50;

	while(itRand == gooseRand)
	{
		itRand = rand() % 50;
		gooseRand = rand() % 50;
	}

	if(itRand > gooseRand)
	{
		output << gameData->itPlayerID << " took " << gooseID << "'s spot!" << std::endl;
		gameData->playerList.set(goosenum, gameData->itPlayerID);
		gameData->itPlayerID = gooseID;
	}
	else
	{
		output << gameData->itPlayerID << " is out!" << std::endl;
		if(gameData->playerList.size() == 1)
		{
			output << "Winner is " << gooseID << "!" << std::endl;
			gameData->itPlayerID = 0;
			return; 
		}
		int newit = rand() % gameData->playerList.size();
		gameData->itPlayerID = gameData->playerList.get(newit);
		gameData->playerList.remove(newit);
	}	

}



