#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
int main()
{
	int kase;
	cin >> kase;
	while (kase--)
	{
		int time = 0;
		// N is how many point
		// S is the maximum of the truck
		// Q is the maximum of the point
		int N, S, Q;
		cin >> N >> S >> Q;
		vector < queue < int > > points;
		for (int n = 0; n < N; n++)
		{
			int num;
			cin >> num;
			queue < int > point;
			while (num--)
			{
				int temp;
				cin >> temp;
				point.push(temp);
			}
			points.push_back(point);
		}

		stack < int > truck;
		bool check = 1;
		int pos = 0;
		while (check)
		{
			while (!truck.empty() && points[pos].size() < Q)
			{
				if (truck.top() != pos + 1)
					points[pos].emplace(truck.top());
				truck.pop();
				time++;
			}
			while (!truck.empty() && truck.top() == pos + 1)
				truck.pop(), time++;
			while (!points[pos].empty() && truck.size() < S)
			{
				truck.emplace(points[pos].front());
				points[pos].pop();
				time++;
			}
			check = 0;
			
			if (!truck.empty())
				check = 1;
			else if(!check)
				for (int n = 0; n < N; n++)
					if (!points[n].empty())
						check = 1;
			if(check)
				time += 2;
			pos = (pos + 1) % N;
		}
		cout << time << endl;
	}
}