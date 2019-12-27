#include <algorithm>
#include <stack>
#include "Trie.h"
#include <iostream>
#include <queue>
using namespace std;

TrieNode::TrieNode()
{
  c = ' ';
  this->parent = NULL;
  inSet = false;
  for(int i = 0; i < 26;i++)
  {
    this->children[i] = NULL;
  }
}
TrieNode::TrieNode(char c, TrieNode* parent)
{ 
  this->c = c;
  this->parent = parent;
  inSet = false;
  for(int i = 0; i < 26; i++)
    {
      this->children[i] = NULL;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

  TrieSet::TrieSet() // a constructor for an empty trie
  {
    this->source = new TrieNode();
  }

  TrieSet::~TrieSet() // destructor
  {
    destruct(this->source);
  }

  void TrieSet::destruct(TrieNode* n)
  {
    if(n == NULL)return;
    for(int i = 0;i < 26;i++)
    {
      destruct(n->children[i]);
    }
    delete n;
  }


  void TrieSet::insert (std::string input)
  {
    string temp = input;
    transform(temp.begin(),temp.end(), temp.begin(), ::tolower);
    TrieNode* tnode = this->source;

    for(unsigned int i = 0; i < temp.size();i++)
    {
      char currentChar = temp[i];
      if(tnode->children[currentChar - 'a'] == NULL) //should this be lowercase a if string is lowercase
      {
        tnode->children[currentChar - 'a'] = new TrieNode(currentChar, tnode);
      }
      tnode = tnode->children[currentChar - 'a'];
    }
    tnode->inSet = true;
  }

  bool TrieSet::has_child(TrieNode* curr)
  {
    for(int i = 0; i < 26;i++)
    {
      if(curr->children[i] != NULL)return true;
    }
    return false;
  }

  void TrieSet::remove (std::string input)
  {
    string temp = input;
    transform(temp.begin(),temp.end(), temp.begin(), ::tolower);
    TrieNode* tnode = prefix(temp);

    for(int i = (int)temp.size(); i > 0; i--)
    {

        if(tnode == NULL) return;
        if(i == (int)temp.size()) tnode->inSet = false;
        if(tnode->parent != NULL && !has_child(tnode) && tnode->inSet == false)
        {
          cout << "trigger";
          tnode = tnode->parent;
          delete tnode->children[(tnode->c) - 'a'];
          tnode->children[(tnode->c) - 'a'] = NULL;
        }
    }
    
  }

  TrieNode* TrieSet::prefix(std::string px) /* returns the TrieNode matching the provided string, or returns NULL ...if it is not the prefix of a word in the Trie. */
  {
    string temp = px;
    transform(temp.begin(),temp.end(), temp.begin(), ::tolower);
    TrieNode* tnode = this->source;

    for(unsigned int i = 0; i < temp.size();i++)
    {
      char current = temp[i];
      if(tnode->children[current - 'a'] == NULL)
      {
        return NULL;
      }
      tnode = tnode->children[current-'a'];
    }
    return tnode;
  }

  void TrieSet::print()
  {
    queue<TrieNode*> q;
    q.push(source);
    while(!q.empty())
    {
      TrieNode* curr = q.front();
      q.pop();
      cout << curr->c << endl;
      for(unsigned int i = 0; i < 26; i++)
      {
        if(curr->children[i] != NULL)q.push(curr->children[i]);
      }
    }
  }

  