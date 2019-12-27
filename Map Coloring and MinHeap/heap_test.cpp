#include "MinHeap.h"
#include <iostream>

using namespace std;

int main() {
for(int i=2;i<=21;i++) {
cout << "D = " << i << endl;
MinHeap<int>* mh;
mh = new MinHeap<int>(i);

  mh->add(100, 2);
  mh->add(400, 7);
  mh->add(300, 3);
  mh->add(500, 10);
  mh->add(1, 1);

  cout << mh->peek() << endl;
  mh->remove();
  
  cout << mh->peek() << endl;
  mh->remove();
  
  cout << mh->peek() << endl;
  mh->remove();
  
  cout << mh->peek() << endl;
  mh->remove();

  cout << mh->peek() << endl;
  mh->remove();

  cout << endl;
  }
}