 #include "rotateBST.h"
 #include <iostream>
 #include <string>

 using namespace std;


// int main(){

// BinarySearchTree<int, int> myTree;

// rotateBST<int,int> myTree2;


// myTree2.insert(make_pair(8, 8));

// myTree2.insert(make_pair(4,4));


// myTree2.insert(make_pair(20, 20));

// myTree2.insert(make_pair(15, 15));

// myTree2.insert(make_pair(13, 13));

// myTree2.insert(make_pair(21, 21));

// myTree2.insert(make_pair(5, 5));

// myTree2.insert(make_pair(3, 3));

// myTree2.print();


// myTree2.transform(myTree2);

// myTree2.BinarySearchTree::print();


// return -1;
// }

int main(){

rotateBST<int, int> myTree1;

rotateBST<int,int> myTree2;




myTree2.insert(make_pair(3, 3));

myTree2.insert(make_pair(4,4));

myTree2.insert(make_pair(1, 1));

myTree2.insert(make_pair(2, 2));




myTree1.insert(make_pair(4, 4));

myTree1.insert(make_pair(1,1));

myTree1.insert(make_pair(3, 3));

myTree1.insert(make_pair(2, 2));


//print both trees
myTree2.print();
myTree1.BinarySearchTree::print();

myTree2.transform(myTree1);


myTree2.print();
myTree1.BinarySearchTree::print();





return -1;
}