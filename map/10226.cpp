#include<iostream>
#include<iomanip>
#include<string>
#include<map>
using namespace std;
int main()
{
	int kase;
	cin >> kase;
	cin.ignore();
	string a;
	getline(cin, a);
	while (kase--)
	{
		string tree;;
		map < string, double > trees;
		int count = 0;
		while (getline(cin, tree), tree != "")
		{
			trees[tree]++;
			count++;
		}
		for (auto it = trees.begin(); it != trees.end(); it++)
			cout << it->first << ' ' << fixed << setprecision(4) << it->second / count * 100 << endl;
		if(kase)
			cout<<endl;
	}
}