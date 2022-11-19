#include<iostream>
#include<set>
using namespace std;
int main()
{
	int days;
	multiset < int > bills;
	while (cin >> days, days)
	{
		long long int total = 0;
		while(days--)
		{
			int kase;
			cin >> kase;
			while (kase != 0 && kase--)
			{
				int temp;
				cin >> temp;
				bills.insert(temp);
			}
			auto it1 = bills.begin(), it2 = --bills.end();
			total += (*it2 - *it1);
			bills.erase(it1);
			bills.erase(it2);
		}
		cout << total << endl;
		bills.clear();
	}
}