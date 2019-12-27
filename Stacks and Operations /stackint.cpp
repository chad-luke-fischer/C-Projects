#include <iostream>
#include <stdlib.h>
#include "stackint.h"

StackInt::StackInt(){}

StackInt::~StackInt()
{

}

/**
   * Returns true if the stack is empty, false otherwise
   */
  bool StackInt::empty() const
  {
  	if(list.empty() == true)
  	{
  		return true;
  	}
  	return false;

  }

  /**
   * Pushes a new value, val, onto the top of the stack
   */
  void StackInt::push(const int& val)
  {
  	list.push_back(val);
  }

  /**
   * Returns the top value on the stack
   */
  int  StackInt::top() const
  {
    if(!list.empty())
    {
      


  	return list.get(list.size()-1);
  }
  }

  /**
   * Removes the top element on the stack
   */
  void StackInt::pop()
  {
  	if (list.empty() == true){return;}
  	list.remove(list.size()-1);
  }
/*
  int main()
  {
  	StackInt* test = new StackInt();
  	test->push(1);
  	test->push(2);
  	test->push(3);
  	std::cout << "Expect 3... " << "Result: " << test->top() << std::endl;
  	test->pop();
  	std::cout << "Expect 2... " << "Result: " << test->top() << std::endl;
  	test->pop();
  	test->pop();
  	std::cout << "Expect true... " << "Result: " << test->empty() << std::endl;

  }
  */
  