#include<iostream>
#include<stack>
#include<string>
using namespace std;
int isp(char x)
{
	switch (x)
	{
	case '(':
	case ')':
		return 8;
	case '*':
	case '/':
		return 2;
	case '+':
	case'-':
		return 3;
	default:
		return 9;
	}
}
int icp(char x)
{
	switch (x)
	{
	case '(':
	case ')':
		return 0;
	case '*':
	case '/':
		return 2;
	case '+':
	case'-':
		return 3;
	default:
		return 0;
	}
}
int main()
{
	int kase;
	cin >> kase;
	string a;
	cin.ignore();
	getline(cin, a);
	while (kase--)
	{
		string str, temp;

		while (getline(cin, temp) && temp != "")
			str += temp;
		stack < char > s;
		for (int n = 0; n < str.size(); n++)
		{
			char x = str[n];
			if (x >= '0' && x <= '9')
				cout << x;
			else if (x == ')')
			{
				while (!s.empty() && s.top() != '(')
				{
					if(s.top() != '(' && s.top() != ' ')
					cout << s.top();
					s.pop();
				}
				if (!s.empty())
					s.pop();
			}
			
			else
			{
				while (!s.empty() && isp(s.top()) <= icp(x))
				{
					cout << s.top();
					s.pop();
				}
					
				s.emplace(x);
			}
		}
		while (!s.empty())
		{
			if(s.top() != ' ' && s.top() != '(')
				cout << s.top();
			s.pop();
		}

		if (kase)
			cout << endl << endl;
		else
			cout << endl;
	}
}