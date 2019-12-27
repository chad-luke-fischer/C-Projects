#include <iostream>
#include <stdlib.h>
#include "selection_sort.h"


Item* findMin(Item * head)
{
	Item * current = head;
	//edge case
	if(head == nullptr)
	{
		return nullptr;
	}
	//edge case
	else if(head->next == nullptr && head->prev == nullptr)
	{
		return head;
	}
	Item * smallest = head;
	int minVal = head->getValue();

	//iterate through list to find the item with minimum value
	while(current->next != nullptr)
	{
		current = current->next;
		if(current->getValue() < minVal)
		{
			smallest = current;
			minVal = current->getValue();
		}
	}
	return smallest;
}

Item* LLSelectionSort(Item * head)
{
	Item* temp = head;
	int count = 0;

	if(temp == nullptr){return nullptr;}

	while(temp != nullptr)
	{
		if(count == 0)
		{
			Item* min = findMin(temp);
			if(min->getValue() != temp->getValue())
			{
				nodeSwap(temp, min);
			}
			head = min;
			count++;
			temp = min->next;
		}
		else
		{
			Item* min = findMin(temp);
			if(min->getValue() != temp->getValue())
			{
				nodeSwap(temp, min);
			}
			temp = min->next;
		}		
	}
	return head;
}

void nodeSwap(Item* node1, Item* node2)
{
	//save prev and next so nodes aren't lost
	Item* node1next = node1->next;
	Item* node1prev = node1->prev;
	Item* node2next = node2->next;
	Item* node2prev = node2->prev;

	if(node1->next == node2)
	{
		if(node1->prev == nullptr && node2->next == nullptr)
		{
			node1->next = node2next;
			node1->prev = node2;
			node2->prev = nullptr;
			node2->next = node1;
		}
		else if(node2->next == nullptr)
		{
			node1->next= nullptr;
			node1prev->next = node2;
			node2->prev = node1prev;
			node1->prev = node2;
			node2->next= node1;
		}
		else if(node1->prev == nullptr)
		{
			node1->next = node2->next;
			node1->prev = node2;
			node2next->prev = node1;
			node2->prev = nullptr;
			node2->next = node1;
		}
		else
		{
			node1->next = node2next;
			node1prev->next = node2;
			node2->prev = node1prev;

			node1->prev = node2;
			node2next->prev = node1;
			node2->next = node1;
		}

	}

	else
	{
		if(node1->prev == nullptr && node2->next == nullptr)
		{
			node1next->prev = node2;
			node2prev->next = node1;
			node2->next = node1next;
			
			node1->next = nullptr;
			node1->prev = node2prev;
			node2->prev = nullptr;
		}
		else if(node2->next == nullptr)
		{
			node1prev->next = node2;
			node2prev->next = node1;
			node1next->prev = node2;
			node1->next  = node2->next;
			node1->prev = node2->prev;
			node2->prev = node1prev;
			node2->next = node1next;
		}
		else if(node1->prev == nullptr)
		{
			node1next->prev = node2;
			node1->next = node2next;
			node1->prev = node2prev;
			node2prev->next = node1;
			node2next->prev = node1;
			node2->prev = node1next->prev;
			node2->next = node1next->next;
		}
		else if(node1->prev == nullptr)
		{
			node1next->prev = node2;
			node1->next = node2next;
			node1->prev = node2prev;
			node2prev->next = node2->next;
			node2next->prev = node1; //here
			node2->prev = nullptr;
			node2->next = node1next->next;
		}
		else
		{
			node2next->prev = node1;
			node2prev->next =  node1;
			node1prev->next = node2;
			node1next->prev = node2;
			node1->next = node2next;  
			node1->prev = node2prev;
			node2->prev = node1prev;
			node2->next = node1next;
		}
	}
}

