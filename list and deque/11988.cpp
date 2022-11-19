#include<iostream>
#include<list>
#include<deque>
#include<string>
using namespace std;
int main()
{
	string str;
	list < char > ans;
	while (getline(cin, str))
	{
		auto it = ans.begin();
		for (int n = 0; n < str.size(); n++)
		{
			if (str[n] == '[')
				it = ans.begin();
			else if (str[n] == ']')
				it = ans.end();
			else
			{
				it = ans.insert(it, str[n]);
				it++;
			}
		}
		for (auto it = ans.begin(); it != ans.end(); it++)
			cout << *it;
		cout << endl;
		ans.clear();
	}

}