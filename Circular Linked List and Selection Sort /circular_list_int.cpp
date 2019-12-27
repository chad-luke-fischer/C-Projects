#include <iostream>
#include <stdlib.h>
#include "circular_list_int.h"


CircularListInt::CircularListInt(){}

CircularListInt::~CircularListInt()
{
	if(count == 0)
	{
		return;
	}

	int sizeOfCircularList = count;

	for(int i=0;i<sizeOfCircularList;i++)
	{
		remove(0);
	}

}



int CircularListInt::get(size_t index) const
{
	if(head == nullptr)
	{
		return 0;
	}
	Item* current = head;
	for (unsigned int i = 0; i < index; i++)
	{
		current = current->next;
	}
	return current->value;
}

size_t CircularListInt::size() const
{
	return count;
}

bool CircularListInt::empty() const
{
	if (count == 0){return true;}
	return false;
}

void CircularListInt::push_back(int value)
{
	Item* newItem = new Item(value);
	Item* current = head;
	//case where the list is empty
	if(empty())
	{
		head = newItem;
		head->next = newItem;
		head->prev = newItem;
		count++;
		return;
	}
	//case where list contains one item
	if (count == 1)
	{
		current->next = newItem;
		current->prev = newItem;
		newItem->next = head;
		newItem->prev = head;
		count++;
		return;
	}
	//any other case
	else
	{
		for (unsigned int i = 0; i < count-1; i++)
		{
			current = current->next;

		}
		current->next = newItem;
		newItem->prev = current; //change to current
		head->prev = newItem; //head prev = newitem
		newItem->next = head; //newitem next = head
		count++;
		return;
	}
}

void CircularListInt::set(size_t index, int value)
{
	Item* current = head;
	for (unsigned int i = 0; i < index; i++)
	{
		current = current->next;
	}
	current->value = value;

}

void CircularListInt::remove(size_t index)
{
	Item* current = head;
	
	for (unsigned int i = 0; i < index; i++)
		{
			current = current->next;
		}
		current->prev->next = current->next;
		current->next->prev = current->prev;

		if (current == head)
		{
			head = current->next;
		}
		delete current;

		count--;
		return;
}

	

