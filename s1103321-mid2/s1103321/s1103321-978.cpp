#include<iostream>
#include<set>
#include<vector>
using namespace std;
int main()
{
	int kase;
	cin >> kase;
	while (kase--)
	{
		int space, SG, SB, temp;
		cin >> space >> SG >> SB;
		multiset < int > armyG, armyB;
		while (SG--)
		{
			cin >> temp;
			armyG.emplace(temp);
		}
		while (SB--)
		{
			cin >> temp;
			armyB.emplace(temp);
		}
		
		while(!armyB.empty() && !armyG.empty())
		{
			vector < int > ans(space);
			for (int n = 0; n < space; n++)
			{
				if (armyG.empty() || armyB.empty())
					break;
				auto it1 = --armyG.end(), it2 = --armyB.end();
				ans[n] = *it1 - *it2;
				armyG.erase(it1);
				armyB.erase(it2);
			}

			for (int n = 0; n < space; n++)
				if (ans[n] > 0)
					armyG.emplace(ans[n]);
				else if (ans[n] < 0)
					armyB.emplace(0-ans[n]);
		}
		if (armyB.empty() && armyG.empty())
			cout << "green and blue died\n";
		else if (armyB.empty())
		{
			cout << "green wins\n";
			for (auto it = armyG.rbegin(); it != armyG.rend(); it++)
				cout << *it << endl;
		}
		else if (armyG.empty())
		{
			cout << "blue wins\n";
			for (auto it = armyB.rbegin(); it != armyB.rend(); it++)
				cout << *it << endl;
		}
		if (kase)
			cout << endl;
	}
}