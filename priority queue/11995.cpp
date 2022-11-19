#include<iostream>
#include<stack>
#include<queue>
using namespace std;
int main()
{
	int kase;
	while (cin >> kase)
	{
		int cmd, num;
		stack < int > type1;
		queue < int > type2;
		priority_queue < int > type3;
		bool check1 = 1, check2 = 1, check3 = 1;
		while(kase--)
		{
			cin >> cmd >> num;
			if (cmd == 1)
			{
				type1.push(num);
				type2.push(num);
				type3.push(num);
			}
			else if (cmd == 2)
			{
				if (check1)
					if (!type1.empty() && type1.top() == num)
						type1.pop();
					else
						check1 = 0;
				if (check2)
					if (!type2.empty() && type2.front() == num)
						type2.pop();
					else
						check2 = 0;
				if (check3)
					if (!type3.empty() && type3.top() == num)
						type3.pop();
					else
						check3 = 0;
			}
		}
		if ((check1 && check2 && check3) || (check1 && check2) || (check1 && check3) || (check2 && check3))
			cout << "not sure\n";
		else if (check1)
			cout << "stack\n";
		else if (check2)
			cout << "queue\n";
		else if (check3)
			cout << "priority queue\n";
		else
			cout << "impossible\n";
	}
}