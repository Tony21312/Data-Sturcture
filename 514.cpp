#include<iostream>
#include<stack>
using namespace std;
int main()
{
	int num;
	while (cin >> num, num)
	{
		while (1)
		{
			stack < int > train, station;
			for (int n = num; n > 0; n--)
				train.emplace(n);

			int temp = 0;
			bool check = 0;

			for (int n = 0; n < num; n++)
			{
				cin >> temp;
				if (temp == 0)
					break;
				if (!station.empty() && station.top() == temp)
					station.pop();
				else
				{
					while (!train.empty() && temp != train.top())
					{
						station.push(train.top());
						train.pop();
					}
					if (!train.empty() && train.top() == temp)
						train.pop();
				}
			}
			if (station.empty() && train.empty())
				check = 1;
			if (temp == 0)
				break;
			if (check)
				cout << "Yes\n";
			else
				cout << "No\n";
		}
		cout << endl;
	}

}