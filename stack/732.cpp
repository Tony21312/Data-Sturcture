#include<iostream>
#include<stack>
using namespace std; 

#define it string::iterator
string str1, str2;
stack < char > temp;

void dfs(it it1, it it2, string ans)
{
	if(it2 == str2.end())
		cout << ans << endl;
	if (it1 != str1.end())
	{
		temp.push(*it1);	
		dfs(it1 + 1, it2,  (ans.empty()) ? ans + 'i' : ans + " i");
		temp.pop();
	}
	if (!temp.empty() && *it2 == temp.top())
	{
		char tmp = temp.top();
		temp.pop();
		dfs(it1, it2 + 1, (ans.empty()) ? ans + 'o' : ans + " o");
		temp.push(tmp);
	}
}
int main()
{
	while (cin >> str1 >> str2)
	{
		string ans;
		cout << "[\n";
		if (str1.size() == str2.size())
			dfs(str1.begin(), str2.begin(), ans);
		cout << "]\n";
	}
}