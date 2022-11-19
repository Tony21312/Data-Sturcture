#include<iostream>
#include<list>
#include<deque>
using namespace std;
int main()
{
	int kase;
	for (int n = 1; cin >> kase; n++)
	{
		int num, numOfCmd;
		cin >> numOfCmd;
		if (kase == 0 && numOfCmd == 0)
			break;
		cout << "Case " << n << ":\n";

		deque < int > sequence;
		for (int n = 0; n < min(kase, numOfCmd); n++)
			sequence.emplace_back(n + 1);

		while (numOfCmd--)
		{
			char cmd;
			cin >> cmd;
			if (cmd == 'N')
			{
				cout << sequence.front() << endl;
				sequence.emplace_back(sequence.front());
				sequence.pop_front();
			}
			else if (cmd == 'E')
			{
				cin >> num;
				for (auto it = sequence.begin(); it != sequence.end(); it++)
					if (*it == num)
					{
						sequence.erase(it);
						break;	
					}
				sequence.emplace_front(num);
			}
		}
	}
}