#include <string>
#include <fstream>
#include "Dictionary.h"
#include "Exceptions.h"
#include "Util.h"
#include <algorithm>

Dictionary::Dictionary(std::string dictionary_file_name):
words()
{
	std::ifstream dictFileStream(dictionary_file_name);

	words = new TrieSet;

	if(!dictFileStream)
	{
		throw FileException("DICTIONARY");
	}

	while(!dictFileStream.eof())
	{
		std::string word;
		dictFileStream >> word;
    	transform(word.begin(),word.end(), word.begin(), ::tolower);

		if (dictFileStream.eof() && word.empty())
		{
			break;
		}

		//makeLowercase(word);
		words->insert(word);
	}
}

Dictionary::~Dictionary()
{
	// default destructor is OK
}

bool Dictionary::isLegalWord(std::string const &word) const
{
	// std::string lowercaseWord(word);
	// makeLowercase(lowercaseWord);
	std::string temp_word = word;
    transform(temp_word.begin(),temp_word.end(), temp_word.begin(), ::tolower);

	TrieNode* temp = words->prefix(temp_word);

	if(temp != NULL)
	{
		if(temp->inSet == true)
		{
			return true;
		}
		else return false;
	}
	return false;
	
	//return words.find(lowercaseWord) != words.end();
}
