#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <math.h>

using namespace std;

struct Node
	{
	Node(int i, int j, char c)
	{
	this->y = i;
	this->x = j;
	this->letter = c;
	}
    int x;
    int y;
    char letter;
	};

int BFS(vector<vector<bool> >& visited, vector<vector<char> >& input, char l, Node start) //param(visited array, map, char, start)
{
	queue<Node> queue; //queue of nodes that will represent the neighbors of start
	queue.push(start); //push in first node
	int countrySize = 0; //keeps track of country size... to be returned 
	visited[start.y][start.x] = true; //mark start as visited

	while(!queue.empty()) //while valid neighbors remain
		{
			for(int a = 0; a <queue.size();a++)
			{
				Node tnode(queue.front()); //set tnode to start of queue
				queue.pop();	//pop off tnode
				countrySize++;	//increment size
				if(tnode.y<input.size()-1) //check cell above tnode
				{
				if((visited[tnode.y+1][tnode.x] == false) && (input[tnode.y+1][tnode.x] == l)){
					queue.push(Node(tnode.y+1,tnode.x, l)); //push right node as neighbor
					visited[tnode.y+1][tnode.x] = true; //mark visited
				}
				}
				if(tnode.y-1>=0) //check cell below tnode
				{
				if((visited[tnode.y-1][tnode.x] == false) && (input[tnode.y-1][tnode.x] == l)){
				queue.push(Node(tnode.y-1,tnode.x, l));
				visited[tnode.y-1][tnode.x] = true;
				}
				}
			if(tnode.x<input[0].size()-1) //check cell right of start
			{
			if((visited[tnode.y][tnode.x+1] == false) && (input[tnode.y][tnode.x+1] == l)){
			queue.push(Node(tnode.y,tnode.x+1, l));
			visited[tnode.y][tnode.x+1] = true;
			}
			}
			if(tnode.x-1>=0) //check cell left of start
			{
			if((visited[tnode.y][tnode.x-1] == false) && (input[tnode.y][tnode.x-1] == l)){
				queue.push(Node(tnode.y,tnode.x-1, l));
				visited[tnode.y][tnode.x-1] = true;
			}
			}
		}
	}
	return countrySize;
}

int main(int argc, char** argv)
{
	vector<vector<bool> > visited;
	vector<vector<char> > input;
	int maxCount = 0;
	int rows, cols;
	char letters;

	if(argc < 2)
	{
		cout << "Error: improper command line argument." << endl;
	}
	ifstream ifile(argv[1]);
	ifile >> letters >> rows >> cols;


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
	
	for(int i = 0; i < rows;i++)
	{
		for(int j = 0; j < cols;j++)
		{
			if (!visited[i][j])
			{
				maxCount = max(maxCount, BFS(visited, input, input[i][j], Node(i,j,input[i][j]))); 
			}
		}
	}
	if(maxCount == 0)maxCount++;
	cout << maxCount << endl;
	return 0;
}