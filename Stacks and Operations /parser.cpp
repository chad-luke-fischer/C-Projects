#include <iostream>
#include <string>
#include <stdlib.h>
#include "stackint.h"
#include <ctype.h>
#include <fstream>

const int OPEN_PAREN = -1;
const int CLOSE_PAREN = -2;
const int SHIFT_RIGHT = -3; //half the following integer
const int SHIFT_LEFT = -4; //double the integer following
const int MULTIPLY = -5;
const int ADDITION = -6;

bool diffOp(std::string line)
{
  StackInt stk2;
  bool flag = false;
    for(unsigned int i = 0; i < line.size();i++)  
      if(line[i] == ' ')
      {
      
      }
      else if(line[i] == '(')
      {
        stk2.push(OPEN_PAREN);
      }
      else if(line[i] == '*')
      {
        stk2.push(MULTIPLY);
      }
      else if(line[i] == '+')
      {
        stk2.push(ADDITION);
      }
      else if(line[i] == '<')
      {
        stk2.push(SHIFT_LEFT);
      }
      else if(line[i] == '>')
      {
        stk2.push(SHIFT_RIGHT);
      }
      else if(isdigit(line[i]))
      {
        //check if number had multiple digits
        int anum = (line[i] - '0');
        while((i < line.size()) && (isdigit(line[i+1])))
        {
          anum = (anum * 10) + (line[i+1] - '0');
          i++;
        }
        stk2.push(anum);
      }
      else if(line[i] == ')')
      {
        bool addition = false;
        bool mult = false;
        while((!stk2.empty())&&(stk2.top() != OPEN_PAREN))
        {
          if(stk2.top() == ADDITION)
          {
            addition = true;
          }
          else if(stk2.top() == MULTIPLY)
          {
            mult = true;
          }
          stk2.pop();
        }
        if (addition&&mult)
        {
          return true;
        }
      }
return false;

}


int main (int argc, char* argv[])
{
  if(argc < 2)
  {
    return 1;
  }
  std::ifstream inputFile(argv[1]);

  StackInt stk;
  bool malformed = false;
  std::string expression;
  while(getline(inputFile, expression))//extract expressions line by line from inputfile
  {
    int open = 0;
    int close = 0;

    for(unsigned int i = 0; i < expression.size();i++)//checks if number of open and close parens is =
    {
      if(expression[i] == '(')
      {
        open++;
      }
      else if(expression[i] == ')')
      {
        close++;
      }
      else if((expression[i] != ')')&&(expression[i] != '(')&&(expression[i] != '+')&&
      (expression[i] != '*')&&(expression[i] != '<')&&(expression[i] != '>')&&(expression[i] != ' ')&&(!isdigit(expression[i])))
      {
        malformed = true;
      }
    }
    if(open != close)
    {
      malformed = true;
    }
    if(diffOp(expression))
    {
      malformed = true;
    }
    
    for (unsigned int i = 0; i < expression.size();i++)
    {
      //Push open parenthesis '(', integers, and operators onto the stack.
      if(expression[i] == ' ')
      {
      
      }
      if(expression[i] == '(')
      {
        stk.push(OPEN_PAREN);
      }
      else if(expression[i] == '*')
      {
        stk.push(MULTIPLY);
      }
      else if(expression[i] == '+')
      {
        stk.push(ADDITION);
      }
      else if(expression[i] == '<')
      {
        stk.push(SHIFT_LEFT);
      }
      else if(expression[i] == '>')
      {
        stk.push(SHIFT_RIGHT);
      }
      else if(isdigit(expression[i]))
      {
        //check if number had multiple digits
        int anum = (expression[i] - '0');
        while((i < expression.size()) && (isdigit(expression[i+1])))
        {
          anum = (anum * 10) + (expression[i+1] - '0');
          i++;
        }
        stk.push(anum);
      }
    //When you encounter a closing parenthesis ')', 
    //pop things from the stack and evaluate them until you pop the open parenthesis '('.
      else if(expression[i] == ')')
      {
        if(stk.empty())
        {
          malformed = true;
        }
        int result;
        while((stk.empty())&&(stk.top() != OPEN_PAREN))
        {
          if(stk.top() < 0) //if top of stack isn't a number:malformed
          {
            malformed = true;
          }
          int temp = stk.top();//should encounter a num first...operands and bit shifts shouldn't be on the right
          if(!stk.empty())stk.pop();
          //should encounter bit shift or operator next

          if(stk.top() == SHIFT_LEFT || stk.top() == SHIFT_RIGHT)//check for bit shift
          {
            while(stk.top() == SHIFT_LEFT || stk.top() == SHIFT_RIGHT)
            {
              if(stk.top() == SHIFT_LEFT)
              {
                temp *= 2;
                if(!stk.empty())stk.pop();
              }
              else if(stk.top() == SHIFT_RIGHT)
              {
                temp /= 2;
                if(!stk.empty())stk.pop();
              }
            }
            result = temp;  //changed this line from result = temp
            stk.push(result);
          }
          else if(stk.top() == MULTIPLY)
          {
            if(!stk.empty())stk.pop();
            int temp2 = stk.top();
            if(!stk.empty())stk.pop();;
            while(stk.top() == SHIFT_LEFT || stk.top() == SHIFT_RIGHT)
            {
              if(stk.top() == SHIFT_LEFT)
              {
                temp2 *= 2;
                if(!stk.empty())stk.pop();
              }
              else if(stk.top() == SHIFT_RIGHT)
              {
                temp2 /= 2;
                if(!stk.empty())stk.pop();
              }
            }
            result = temp * temp2;
            stk.push(result); 
          }
          else if(stk.top() == ADDITION)
          {
            if(!stk.empty())stk.pop();
            int temp2 = stk.top();
            if(!stk.empty())stk.pop();
            while(stk.top() == SHIFT_LEFT || stk.top() == SHIFT_RIGHT)
            {
              if(stk.top() == SHIFT_LEFT)
              {
                temp2 *= 2;
                if(!stk.empty())stk.pop();
              }
              else if(stk.top() == SHIFT_RIGHT)
              {
                temp2 /= 2;
                if(!stk.empty())stk.pop();
              }
            }
            result = temp + temp2;
            stk.push(result);
          }
        }
        if(!stk.empty())stk.pop();
        while((!stk.empty()) &&(stk.top() == SHIFT_LEFT || stk.top() == SHIFT_RIGHT))
        {
          if(stk.top() == SHIFT_LEFT)
          {
            result *= 2;
            if(!stk.empty())stk.pop();
          }
          else if(stk.top() == SHIFT_RIGHT)
          {
            result /= 2;
            if(!stk.empty())stk.pop();
          }
        }
        stk.push(result);
      }

    }

    if(malformed == true)
    {
      std::cout << "Malformed" << std::endl;
    }
      
    else
    {
      std::cout << stk.top() << std::endl;
    }
    while(!stk.empty())
    {
      if(!stk.empty())stk.pop();
    }
    malformed = false;
  }
}



      