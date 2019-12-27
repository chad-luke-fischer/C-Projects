#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

void rec(string words[], int num)
{
    //base
    if (num == 0){return;}
    cout << words[num-1];
    cout << endl;
    rec(words, num-1);
}

int main(int argc, char *argv[]) 
{
  ifstream in_file;
  in_file.open(argv[1]);
  
  int numWords;
  in_file >> numWords;
  if (argc < 2)
  {
    cout << "Command line error: Enter more arguments" << endl;
    return 1;
  }
  if (in_file.fail())
  {
    cout << "Error" << endl;
    return 1;
  }
  string words[numWords];
  for (int i = 0; i < numWords; i++)
  {
      in_file >> words[i];
  }
  rec(words, numWords);
}

