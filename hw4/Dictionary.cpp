#include "Dictionary.h"
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

/* The constructor gets passed the name of the file from which
	   to read the word list. */
	Dictionary::Dictionary (std::string dictionary_file_name)
	{
		ifstream ifile(dictionary_file_name);
		string curr = "";
		while(getline(ifile, curr))
		{
			vector.push_back(curr);
		}
		//sort in the constructor?



	}

	Dictionary::~Dictionary ()
	{

	}

	/* Checks whether the given word is in the dictionary, and returns true if so.
	   Case should not matter. Must run in O(logn) for the number of words in the dictionary. */
	bool Dictionary::isLegalWord (std::string const & word) const
	{
		string tempWord = word;
		transform(tempWord.begin(),tempWord.end(), tempWord.begin(), ::tolower);
		return binary_search(vector.begin(), vector.end(), tempWord);
	}