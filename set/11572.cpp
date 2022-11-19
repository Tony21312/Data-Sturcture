#include<iostream>
#include<vector>
#include<queue>
#include<unordered_set>
using namespace std;
int main()
{
	int kase;
	cin >> kase;
	while (kase--)
	{
		int number, max = 0;
		cin >> number;
		unordered_set < int > snowflakes;
		queue< int > tempSnow;
		while (number--)
		{
			int temp;
			cin >> temp;
	
			while (snowflakes.count(temp))
			{
				if (snowflakes.size() > max)
					max = snowflakes.size();
				snowflakes.erase(tempSnow.front());
				tempSnow.pop();
			}
			
			snowflakes.insert( temp);
			tempSnow.push(temp);
		}

		if (snowflakes.size() > max)
			max = snowflakes.size();

		cout << max << endl;
	}
}