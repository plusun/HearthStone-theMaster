#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

vector<int> sep(char* s, char c = '/')
{
	string str;
	vector<int> vi;
	vi.clear();
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == c)
		{
			vi.push_back(atoi(str));
			str.clear();
		}
		else
		{
			str += s[i];
		}
	}
	return vi;
}