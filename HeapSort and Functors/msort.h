#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <class T, class Comparator>
  void mergeSort (std::vector<T>& myArray, int k, Comparator comp)
  {
  	std::vector<T> arr(myArray);
  	mergeRecurse(myArray, arr, k, comp, 0, myArray.size()-1);
  }

template<class T, class Comparator>
void mergeRecurse(std::vector<T>& myArray, std::vector<T>& arr, int k, Comparator comp, int start, int end)
{
	std::vector<int> indices;
	std::vector<std::pair<int,int> > _indices;
  if (start < end)
  {

  	//selection sort if subbaray size less than or = k
  	if((end - start + 1) <= k)
  	{
  		for(int i = start; i < end;i++) //changed <=
  		{
  			for(int j = i+1; j <= end; j++)
  			{
  				if(comp(myArray[j], myArray[i]))
  				{
  					T temp = myArray[i];
  					myArray[i] = myArray[j];
  					myArray[j] = temp;
  				}
  			}
  		}
  	}
  	else
  	{
  		int arraySize = (end-start+1);
  		int size = (end-start + 1)/k;
  		int remainder = (end-start + 1)%k;
  		int _remainder = (end-start + 1)%k;
  		int Cremainder = (end-start + 1)%k;

  		for(int i = 0; i < k; i++)//push back size of indices
  		{
  			if(remainder == 0){indices.push_back(size);}
  			else if(remainder > 0)
  			{
  				indices.push_back(size+1);
  				remainder--;
  			}

  		}
  		for(int i = 0; i < k; i++)//change indices to _indices which holds pairs of start and end of each partition
  		{
  			if(_remainder > 0)
  			{
  				int first, second;
  				first = i*indices[i]+start;
  				second = start + _remainder + (i+1)*indices[i] - 1;
  				_indices.push_back(std::make_pair(first,second));
  				_remainder--;
  			}
  			else
  			{
  				int first, second;
  				first = i*indices[i]+Cremainder+start;
  				second = (i+1)*indices[i]+Cremainder+start-1;
  				_indices.push_back(std::make_pair(first, second));
  			}
  		}
  		for(int i = 0; i < k; i++)//call recursive function k times
  		{
  			mergeRecurse(myArray, arr, k, comp,_indices[i].first,_indices[i].second);
  		}
  		merge(myArray, arr, arraySize, k, start, comp, _indices);
 	}
  }
}

template<class T, class Comparator>
void merge(std::vector<T>& myArray, std::vector<T>& arr, int arraySize, int k, int start, Comparator comp, std::vector<std::pair<int, int> > _indices )
{
	std::vector<int> count; //vector for starting indices
	std::vector<int> max; //vector for end indices
	for(int i = 0; i < k; i++)
	{
		std::cout << myArray[i];
	}

	for(int i = 0; i < k; i++)
	{
		count.push_back(_indices[i].first);
		max.push_back(_indices[i].second);

	}

	for(int i = _indices[0].first; i < _indices[0].first+arraySize;i++)
	{
		int minimumIndex=-1, difference=0;
		for(int z = 0; z < k; z++)
		{
			if(count[z] <= max[z])
			{
				minimumIndex = count[z]; //assign to first non empty partition... check to see if start > end
				difference = z;
				break;
			}
		}
		for(int b = 0; b < k;b++)
		{
			if((count[b] <= max[b])&&(comp(myArray[count[b]], myArray[minimumIndex])))
			{
				minimumIndex = count[b];
				difference = b;
			}
		}
		arr[i] = myArray[minimumIndex];
		count[difference]++;
	}
	for(int i = 0 + start; i < arraySize + start;i++)
	{
		myArray[i] = arr[i];
	}
}

//int main()
//{
//	std::vector<int> vec = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
 // std::vector<int> sortedVec = vec;

  //std::sort(vec.begin(), vec.end(), NumComp());

  //NumComp comp;

 // for (int k = 2; k <= 10; k++) {
   // sortedVec = {1,2,3,4,5,6,7,8,9,10};
  //  mergeSort(sortedVec, k, comp);
    
  



