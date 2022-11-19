#include<iostream>
#include<map>
#include<algorithm>
#include<string>
using namespace std;
int main()
{
	int stu;
	while (cin >> stu, stu)
	{
		map < string, int > course;
		
		while (stu--)
		{
			string class1, arr[5] = {};
			for(int n = 0; n < 5; n++)
			{
				cin >> class1;
				arr[n] = class1;
			}
			sort(begin(arr), end(arr));
			class1 = "";
			for (int n = 0; n < 5; n++)
				class1 += arr[n];
			course[class1]++;
		}
		int max = 0, total = 0;

		for (auto it = course.begin(); it != course.end(); it++)
			if (it->second > max)
				max = it->second;
		for (auto it = course.begin(); it != course.end(); it++)
			if (it->second == max)
				total += max;
		cout << total << endl;
	}
}