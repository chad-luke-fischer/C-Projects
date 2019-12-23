#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main()
{
	string steps;
	cout << "Please enter a string indicating your sequence of steps in the cave." << endl;
	getline(cin, steps);
	bool flag = false;
	bool valid = true;
	while(steps.size()>0)
	{
		for(int i = 0; i < steps.size();i++)
		{
			flag = false;
			if (((steps[i] == 'n')&&(steps[i+1] == 's'))||
				((steps[i] == 's')&&(steps[i+1] == 'n'))||
				((steps[i] == 'e')&&(steps[i+1] == 'w'))||
				((steps[i] == 'w')&&(steps[i+1] == 'e')))
			{
				steps.erase(i,2);
				flag = true;
				break;
			}
			if((steps[i]!='n' && steps[i]!='s' && steps[i]!='e' && steps[i]!='w')||(steps[i]==' '))
			{
				cout << "invalid" << endl;
				valid = false;
				return 0;
			}

		}
		if(steps.size() > 0 && !flag && valid){cout << "not rolled up" << endl;break;}

	}
	if(steps.size()==0){cout << "rolled up" << endl;}
	
	
}	

