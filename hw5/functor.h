#include <string>
#include <map>
#include <iostream>

struct AlphaStrComp {
  bool operator() (const std::string& lhs, const std::string& rhs)
  { // Uses string's built in operator<
    // to do lexicographic (alphabetical) comparison
    return (lhs < rhs);
  }
};

struct LengthStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs)
  { // Compares strings by size;
    // Breaks ties by lexicographic comparison
    return (   (lhs.size() < rhs.size())
            || (lhs.size() == rhs.size() && lhs < rhs));
  }
};


struct NumStrComp 
{
  bool operator()(const std::string& lhs, const std::string& rhs)
  {
    //adds up all the numbers assigned to all digits and letters in the string
    // sorts by the sum
    std::map<char,int> vals;
    for(int i = 0; i < 9; i++)
    {
      vals['i'] = i;
    }
    for(int i = 0; i < 26;i++)
    {
      vals['A' + i] = i + 10;
      vals['a' + i] = i + 10;
    }
    int sum1 = 0, sum2 = 0;
    for(int i = 0; i < lhs.size(); i++)
    {
      if(vals.count(vals[lhs[i]]))sum1 += vals[lhs[i]];
    }
    for(int i = 0; i < rhs.size();i++)
    {
      if(vals.count(vals[lhs[i]]))sum2 += vals[rhs[i]];
    }
    return (sum1 < sum2)||((sum1==sum2)&&(lhs<rhs));

  }
};
