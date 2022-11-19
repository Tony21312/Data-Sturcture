#include<iostream> 
#include<vector>
#include<queue>
using namespace std;
int main()
{
	int num, temp;
	while (cin >> num, num)
	{
		priority_queue < int, vector < int > , greater < int > > data;

		while (num--)
		{
			cin >> temp;
			data.emplace(temp);
		}
		temp = 0; num = 0;
		bool check = 0;
		while (data.size() > 1)
		{
			temp = data.top();
			data.pop();
			temp += data.top();
			data.pop();
			data.emplace(temp);
			num += temp;
			
		}
		cout << num << endl;
	}
}