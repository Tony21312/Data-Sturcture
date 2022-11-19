#include<iostream>
#include<queue>
using namespace std;
int main()
{
	int kase;
	cin >> kase;
	while (kase--)
	{
		int ferryLength, cars;
		cin >> ferryLength >> cars;
		queue < int > left, right;
		while (cars--)
		{
			int length;
			string str;
			cin >> length >> str;
			(str == "left") ? left.push(length) : right.push(length);
		}

		ferryLength *= 100;
		int count = 0, length = ferryLength;
		bool pos = 1; // 1 : left, 0 : right
		while (!left.empty() || !right.empty())
		{
			length = ferryLength;
			if(pos)
				while (!left.empty() && length > left.front())
				{
					length -= left.front();
					left.pop();
				}
			else
				while (!right.empty() && length > right.front())
				{
					length -= right.front();
					right.pop();
				}
			pos = !pos;
			count++;
		}
		cout << count << endl;
	}
}