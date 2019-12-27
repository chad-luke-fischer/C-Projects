
#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
	BinarySearchTree<int, string> myTree;
	myTree.insert(make_pair(3, "three"));
	myTree.insert(make_pair(4, "four"));
	myTree.insert(make_pair(5, "five"));
	myTree.insert(make_pair(1, "one"));
	myTree.insert(make_pair(2, "two"));



	myTree.print();

	myTree.remove(3);

	myTree.print();


	return -1;
}