#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
int main()
{
	int kase;
	cin >> kase;
	while (kase--)
	{
		int field, gArmy, bArmy, temp;
		cin >> field >> gArmy >> bArmy;
		multiset< int > gNum, bNum;
		for (int n = 0; n < gArmy; n++)
		{
			cin >> temp;
			gNum.insert(temp);
		}
		for (int n = 0; n < bArmy; n++)
		{
			cin >> temp;
			bNum.insert(temp);
		}

		while(!gNum.empty() && !bNum.empty())
		{
			vector< int > tempB;
			for (int n = 0; n < field; n++)
			{
				if (gNum.empty() || bNum.empty())
					break;
				tempB.push_back(*gNum.rbegin() - *bNum.rbegin());
				auto it = gNum.end();
				gNum.erase(--it);
				it = bNum.end();
				bNum.erase(--it);
			}	
			for (int n = 0; n < tempB.size(); n++)
			{
				if (tempB[n] > 0)
					gNum.insert(tempB[n]);
				else if (tempB[n] < 0)
					bNum.insert(-tempB[n]);
			}
			tempB.clear();
		}

		if (gNum.empty() && bNum.empty())
			cout << "green and blue died\n";
		else if (gNum.empty())
		{
			cout << "blue wins\n";
			for (auto it = bNum.rbegin(); it != bNum.rend(); it++)
				cout << *it << endl;
		}
		else if (bNum.empty())
		{
			cout << "green wins\n";
			for (auto it = gNum.rbegin(); it != gNum.rend(); it++)
				cout << *it << endl;
		}
		if (kase)
			cout << endl;
	}
}