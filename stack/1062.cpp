#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main()
{
	string str;
	int count = 1;
	while (cin >> str && str != "end")
	{
		vector < char > Stack;
		Stack.push_back(str[0]);
		for (int i = 1; i < str.size(); i++)
		{
			if (Stack.back() < str[i])
				Stack.push_back(str[i]);
			else
				*lower_bound(Stack.begin(), Stack.end(), str[i]) = str[i];
		}
		cout << "Case " << count++ << ": " << Stack.size() << endl;
	}
}