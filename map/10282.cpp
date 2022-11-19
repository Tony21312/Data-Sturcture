#include<iostream>
#include<map>
#include<string>
using namespace std;
int main()
{
	map <string, string> dic;
	string temp, english, foreign;
	while (getline(cin, temp) && temp != "")
	{
		int pos = temp.find(' ');
		english = temp.substr(0, pos);
		foreign = temp.substr(pos + 1);
		dic[foreign] = english;
	}

	while (getline(cin, foreign) && foreign != "")
	{
		if (!dic[foreign].size())
			cout << "eh" << endl;
		else
			cout << dic[foreign] << endl;
	}	
}