#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>

using namespace std;


vector<char> neighbors(vector<vector<char> >& input, vector<vector<bool> >& visited, vector<char>& borders,
	int i, int j, int rows, int cols) //function returns vector of chars indicating the neighbors of a cell
{
	if(i < rows-1) //check if incrementation of i stays inside bounds
	{
		if(!visited[i+1][j] && input[i+1][j]==input[i][j]) //check if visited and same char as previous cell
		{
			visited[i+1][j] = true; //mark visited as true
			neighbors(input, visited, borders, i+1, j, rows, cols); //if visited...recursive call
		}
		else if(input[i+1][j] != input[i][j]) //if different char
		{
			bool neighborAlready = false;
			for(int curr = 0; curr < borders.size();curr++)
			{
				if(input[i+1][j] == borders[curr])neighborAlready = true; //checks if neighbor is already accounted for
			}
			if(!neighborAlready)borders.push_back(input[i+1][j]); //only push back border if not neighbor already
		}
	}
	if(i >= 1) //check bounds 
	{
		if(!visited[i-1][j] && input[i-1][j]==input[i][j])
		{
			visited[i-1][j] = true;
			neighbors(input, visited, borders, i-1, j, rows, cols);
		}
		else if(input[i-1][j] != input[i][j])
		{
			bool neighborAlready = false;
			for(int curr = 0; curr < borders.size();curr++)
			{
				if(input[i-1][j] == borders[curr])neighborAlready = true;
			}
			if(!neighborAlready)borders.push_back(input[i-1][j]);
		}
	}
	if(j < cols-1) //check bounds
	{
		if(!visited[i][j+1] && input[i][j+1]==input[i][j])
		{
			visited[i][j+1] = true;
			neighbors(input, visited, borders, i, j+1, rows, cols);
		}
		else if(input[i][j+1] != input[i][j])
		{
			bool neighborAlready = false;
			for(int curr = 0; curr < borders.size();curr++)
			{
				if(input[i][j+1] == borders[curr])neighborAlready = true;
			}
			if(!neighborAlready)borders.push_back(input[i][j+1]);
		}
	}

	if(j >= 1) //check bounds
	{
		if(!visited[i][j-1] && input[i][j-1]==input[i][j])
		{
			visited[i][j-1] = true;
			neighbors(input, visited, borders, i, j-1, rows, cols);
		}
		else if(input[i][j-1] != input[i][j])
		{
			bool neighborAlready = false;
			for(int curr = 0; curr < borders.size();curr++)
			{
				if(input[i][j-1] == borders[curr])neighborAlready = true;
			}
			if(!neighborAlready)borders.push_back(input[i][j-1]);
		}
	}
	return borders;
}


vector<pair<char,int> > color(vector<vector<char> >& input, vector<vector<bool> > visited, int rows, int cols)
{
	vector<pair<char, int>> colored_regions;
	bool first = true;
	vector<char> borders;
	vector<int> colors;

	for (int i = 1; i < 5;i++){colors.push_back(i);} //push back numbers 1-4 which will represent colors

	for(int i = 0; i < rows;i++)
	{
		for(int j = 0; j < cols;j++)
		{
			if(visited[i][j] == true){continue;} //if cell has been discovered continue
			else
			{
				vector<char> _neighbors = neighbors(input, visited, borders, i, j, rows, cols);
				visited[i][j] = true;
				if(first) //handles instance of first coloring
				{
					colored_regions.push_back(std::make_pair(input[i][j], colors[0])); //change from rand
					borders.clear();
					first = false;
				}
				else //coloring all other countries
				{
					for(int z = 0; z < colors.size();z++) //loop through 4 colors
					{
						bool flag = false;
						for(int q = 0; q < _neighbors.size();q++) //loop through neighbors of country
						{
							for(int b = 0; b < colored_regions.size();b++) //loop through countries
							{

								if(colored_regions[b].first == _neighbors[q] && colors[z] == colored_regions[b].second)
								{
									flag = true;
								}
							}
						}
						if(!flag) //push region only if its not already a neighbor and the color is not the same as its neighbor
						{
							colored_regions.push_back(std::make_pair(input[i][j], colors[z])); //push back new region with its color
							borders.clear(); //get rid of borders 
							break;
						}
					}
				}
			}
		}
	}
	return colored_regions;
}



int main(int argc, char** argv)
{
	vector<vector<bool> > visited;
	vector<vector<char> > input;
	int maxCount = 0;
	int rows, cols, numLetters;

	if(argc < 2)
	{
		cout << "Error: improper command line argument." << endl;
	}
	ifstream ifile(argv[1]);
	ifile >> numLetters >> rows >> cols;
	string lineChars;
	getline(ifile, lineChars);

	for(int i = 0; i < rows; i++) //fill up input and visited arrays 
	{
		vector<char> charLine;
		vector<bool> boolLine;
		getline(ifile, lineChars);
		for(int j = 0; j < cols;j++)
		{
			charLine.push_back(lineChars[j]);
			boolLine.push_back(false);
		}
		input.push_back(charLine);
		visited.push_back(boolLine);
	}

	vector<pair<char,int> > answer = color(input, visited, rows, cols);
	std::sort(answer.begin(), answer.end());
	for(int i = 0; i < answer.size();i++)
		{
			cout << answer[i].first << " " << answer[i].second << endl;
		}
	return 0;
}