#include "Board.h"
#include <fstream>
#include <vector>

using namespace std;

/* constructor that initializes the board state with an empty board
           and the size and bonuses and start square based on the given file. */
	Board::Board (std::string board_file_namey)
	{
		
		std::fstream ifile(board_file_namey);

		ifile >> width >> height;
		ifile >> _startx >> _starty;

		_vector.resize(height, vector<Square*>(width, 0));

		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				char current = ' ';
				ifile >> current;
				if(current == 't')//wmult
				{
					bool start = false;
					if(i == _starty-1 && j == _startx-1){start = true;}
					Square* square = new Square(0,3,start);
					_vector[i][j] = square;

				}
				else if(current == '.')
				{
					bool start = false;
					if(i == _starty-1 && j == _startx-1){start = true;}
					Square* square = new Square(0,0,start);
					_vector[i][j] = square;

				}
				else if(current == '2')//lmult
				{
					bool start = false;
					if(i == _starty-1 && j == _startx-1){start = true;}
					Square* square = new Square(2,0,start);
					_vector[i][j] = square;

				}
				else if(current == 'd')//wmult
				{
					bool start = false;
					if(i == _starty-1 && j == _startx-1){start = true;}
					Square* square = new Square(0,2,start);
					_vector[i][j] = square;
				}
				else if(current == '3')//lmult
				{
					bool start = false;
					if(i == _starty-1 && j == _startx-1){start = true;}
					Square* square = new Square(3,0,start);
					_vector[i][j] = square;
				}
			}
		}
	}

	Board::~Board ()
	{
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				delete _vector[i][j];
			}
		}

	}

	/* returns a vector of all words that would be formed by executing the
           given move. The first element of the pair is a string containing the word
           formed, and the second element is the score that that word earns
           (with all multipliers, but not the 50-point bonus for all letters).

       Words returned are all in uppercase.

	   The last entry of the vector is always the "main" word formed
	   in the direction chosen by the user; the others could be in arbitrary
	   order. (This is helpful for backtracking search.)

	   This function does not check that the words formed are actually in the dictionary.
	   The words returned from this function must be checked against the dictionary to
	   determine if the move is legal.	*/
	std::vector<std::pair<std::string, unsigned int> > Board::getPlaceMoveResults(const PlaceMove &m) const
	{
		

	}

	/* Executes the given move by taking tiles and placing them on the board.
	   This function does not check for correctness of the move, so could
	   segfault or cause other errors if called for an incorrect move.
	   When a blank tile '?' is placed on the board, it is treated as a letter,
	   i.e., the corresponding square has that letter (with score 0) placed on it.
	*/
	void Board::executePlaceMove (const PlaceMove & m)
	{

	}

	/* Returns a pointer to the Square object representing the
       (y,x) position of the board. Indexing starts at 1 here.
	   This is needed only to display the board. */
	Square * Board::getSquare (size_t x, size_t y) const
	{
		return _vector[x-1][y-1];
	}

	/* Returns the number of rows of the board.*/
	size_t Board::getRows() const
	{
		return height;
	}

	/* Returns the number of columns of the board.*/
	size_t Board::getColumns() const
	{
		return width;
	}