#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
class Data
{
public:
	Data()
	{
	}
	Data(int t, int p)
		:time(t), position(p)
	{
	}

	int time;
	int position; // ans' position
};
using namespace std;
int main()
{
	int kase;
	cin >> kase;
	while (kase--)
	{
		
		int n, t, m;
		cin >> n >> t >> m;
		queue < Data > right, left;
		for (int i = 0; i < m; i++)
		{
			string str;
			int time;
			cin >> time >> str;
			bool temp = (str == "left") ? 1 : 0;
			(temp) ? left.emplace(Data(time , i)) : right.emplace(Data(time, i));
		}	

		vector < int > ans(m);
		bool pos = 1; // the position of ferry, 1 is the left, 0 is right
		int time = 0, temp = 0; // temp is the value of minimum (left/right) time
		while (!left.empty() || !right.empty())
		{
			int count = 0;

			// calculate time
			if (!left.empty() && !right.empty())
				temp = min(left.front().time, right.front().time);
			else if (left.empty())
				temp = right.front().time;
			else if (right.empty())
				temp = left.front().time;
			time = max(time, temp);
			
			if (pos)
			{
				while (!left.empty() && left.front().time <= time && count < n)
				{
					ans[left.front().position] = time + t;
					left.pop();
					count++;
				}
			}
			else
			{
				while (!right.empty() && right.front().time <= time && count < n)
				{
					ans[right.front().position] = time + t;
					right.pop();
					count++;
				}
			}
			time += t;
			pos = !pos;
		}
		for (auto& n : ans)
			cout << n << endl;

		if (kase)
			cout << endl;
	}
}