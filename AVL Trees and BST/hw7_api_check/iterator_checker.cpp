#include <bst.h>

void testIteratorInterface()
{
	BinarySearchTree<int, double>::iterator it;
	const BinarySearchTree<int, double>::iterator invalid(nullptr);
	std::pair<int, double>& item = it.operator*();
	std::pair<int, double>* itemAddr = invalid.operator->();
	if (item.first == itemAddr->first)
	{
		item.second = itemAddr->second;
	}
	if (it == invalid || it != invalid)
	{
		it = invalid;
	}
	++(++it);
}

void testBSTIterator()
{
	const BinarySearchTree<int, double> bst;
	BinarySearchTree<int, double>::iterator it = bst.begin();
	BinarySearchTree<int, double>::iterator end = bst.end();
	BinarySearchTree<int, double>::iterator found = bst.find(5);
	if (it == end || found == end)
	{
		return;
	}
}

int main(int argc, char* argv[])
{
	testIteratorInterface();
	testBSTIterator();
	return 0;
}