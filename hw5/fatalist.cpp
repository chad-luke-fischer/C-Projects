#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool FatalistHypothesis(std::vector<std::pair<int,int> > grades)
{
	if(grades.empty())return true;
	sort(grades.begin(), grades.end()); //sort by first int
	for(int i = 0; i < grades.size()-1;i++)
	{
		//if second values are not in correct order...return false
		if(grades[i].second > grades[i+1].second){return false;}
	}
	sort(grades.begin(), grades.end(), [](const std::pair<int,int> &left, const std::pair<int,int> &right) {
    return left.second < right.second;}); //sort by second int
	for(int i = 0; i < grades.size()-1;i++)
	{
		//if first values are not in correct order...return false
		if(grades[i].first > grades[i+1].first){return false;}
	}
	return true;
}

