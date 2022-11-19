#include<iostream>
#include<string>
#include<queue>
using namespace std;
class Register
{
	int num;
	int period;
	int time;
public:
	Register(int n, int p, int t)
		:num(n), period(p), time(t)
	{
	}
	// operator< is greater in fact
	bool operator<(const Register& newest)const 
	{
		if (time == newest.time) 
			return num > newest.num;
		else 
			return time > newest.time;
	}
	void outNum()
	{
		cout << num << endl;
	}
	void setTime()
	{
		time += period;
	}
};
int main()
{
	string register1;
	int num, period;
	priority_queue < Register > data;
	while (cin >> register1, register1 != "#")
	{
		cin >> num >> period;
		data.emplace(Register(num, period, period));
	}
	cin >> num;
	while (num--)
	{
		Register temp = data.top();
		data.pop();
		temp.outNum();
		temp.setTime();
		data.push(temp);
	}
}