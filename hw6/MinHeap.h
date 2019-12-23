  #include <vector>
  #include <stdexcept>

 template <class T>
  class MinHeap {
     public:
       MinHeap (int d);
       /* Constructor that builds a d-ary Min Heap
          This should work for any d >= 2,
          but doesn't have to do anything for smaller d.*/

       ~MinHeap ();

       void add (T item, int priority);
         /* adds the item to the heap, with the given priority. */

       const T & peek () const;
         /* returns the element with smallest priority.  
            Break ties however you wish.  
            Throws an exception if the heap is empty. */

       void remove ();
         /* removes the element with smallest priority.
            Break ties however you wish.
            Throws an exception if the heap is empty. */

       bool isEmpty () const;
         /* returns true iff there are no elements on the heap. */

   private:
      // whatever you need to naturally store things.
      // You may also add helper functions here.
        std::vector<std::pair<T, int> > heapVector; //creates heap vector with items and respective priority
        void trickle_down(int index); //bubbles down an item until it reaches valid heap placement
        void trickle_up(int index); //bubbles up and item until it reaches valid placement
        int d_ary; //
  };

  template<class T>
  MinHeap<T>::MinHeap(int d)
  {
    if(d > 2)d_ary = d;
    else d_ary = 2;
  }

  template<class T>
  MinHeap<T>::~MinHeap(){}

  template<class T>
  void MinHeap<T>::add(T item, int priority)
  {
    if(heapVector.size() == 0) //handles adding when size is zerp
    {
      heapVector.push_back(std::make_pair(item, priority));
      return;
    }
    heapVector.push_back(std::make_pair(item, priority)); //otherwise push back pair and trickle down
    trickle_up(heapVector.size()-1);
  }

  template<class T>
  bool MinHeap<T>::isEmpty() const //returns true if heap is empty...false otherwise
  {
    return (this->heapVector.size() == 0);
  }

  template<class T>
  void MinHeap<T>::trickle_up(int idx) //swaps an item and its parent recursively until minheap is valid
  {
    int parent = (idx-1)/d_ary; //parent assignment
    if(idx<=0)return; //base case
    else
    {
      if(heapVector[idx].second <= heapVector[parent].second)
      {
        std::iter_swap(heapVector.begin()+idx,heapVector.begin()+parent);
      }
    }
    trickle_up(parent); //recursive call
  }

  template<class T>
  void MinHeap<T>::trickle_down(int idx)
  {
    int minimum = (idx*d_ary+1); //assign min item

    if(minimum >= (int)heapVector.size())return; //base case
    else
    {
      for(int i = 0; i < d_ary;i++)
      {
        if((idx*d_ary+1)+i >= (int)heapVector.size())break;
        else
        {
          if(heapVector[(idx*d_ary+1)+i].second < heapVector[minimum].second){minimum = (idx*d_ary+1)+i;}
        }
      }
      if(heapVector[minimum].second <= heapVector[idx].second)
      {
        std::iter_swap(heapVector.begin()+minimum, heapVector.begin()+idx); //swaps top and min...recursively calls
      }
      else return;
    }
    trickle_down(minimum); //recursive trickle down call
  }

  template<class T>
  T const & MinHeap<T>::peek() const //returns top of the heap
  {
    if(isEmpty())throw std::logic_error("Unable to find top of empty heap"); //throw exception if heap isempty
    else return heapVector[0].first; //assuming heapVector has at least one element
  }

  template<class T>
  void MinHeap<T>::remove()
  {
    if(isEmpty()) //handles attemopt to pop when heap is empty
    {
      throw std::logic_error("Unable to pop off empty heap");
    }
    else if(heapVector.size() == 1) //handles removing an item when size is one
    {
      heapVector.erase(heapVector.begin());
      return;
    }
    else if(heapVector.size() == 2) //handles removing item when size is 2
    {
      int current_idx = heapVector.size()-1;
      heapVector[0] = heapVector[current_idx];
      heapVector.pop_back();
      return;
    }
    else
    {
    int current_idx = heapVector.size()-1; //otherwise set top to bottom and trickle down
    heapVector[0] = heapVector[current_idx];    
    heapVector.pop_back();
    trickle_down(0);
    }
  }

 