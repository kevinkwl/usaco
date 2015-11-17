/*
ID: kevinli7
PROG: namenum
LANG: C++11
*/
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;
/*string match[8];	
map<string, bool> dict;

void init()
{
	match[0] = "ABC";
	match[1] = "DEF";
	match[2] = "GHI";
	match[3] = "JKL";
	match[4] = "MNO";
	match[5] = "PRS";
	match[6] = "TUV";
	match[7] = "WXY";
}
void genName(string &str, vector<string> &name, string cur,int idx)
{
	if (idx >=  str.size())
		return;
	for (int i = 0 ; i < 3; ++i)
	{
		string s = cur + match[str[idx]-'2'][i];
		if (idx == str.size() - 1)
		{
			if (dict[s])
			name.push_back(s);
		}
		else
		{
			genName(str, name, s, idx+1);
		}
	}
}
void genName(string &str, vector<string> &name)
{
	genName(str,name,"",0);
}
int main()
{
	init();
	ifstream dic("dict.txt");
	ifstream fin("namenum.in");
	ofstream fout("namenum.out");
	string buffer;
	while(dic >> buffer)
		dict[buffer] = true;
	fin >> buffer;
	vector<string> name;
	genName(buffer, name);
	bool flag = false;
	for (auto c : name)
	{
		fout << c << endl;
		flag = true;
	}
	if (!flag)
		fout << "NONE" << endl;


}*/
char namenum[26] = {'2','2','2','3','3','3','4','4','4',
					'5','5','5','6','6','6','7',' ','7',
					'7','8','8','8','9','9','9',' '};
int main()
{
	ifstream dic("dict.txt");
	ifstream fin("namenum.in");
	ofstream fout("namenum.out");
	string buffer;
	map<string, string> dict;
	char str[20];
	while(dic >> buffer)
	{
		memset(str,0, 20*sizeof(char));
		bool flag = false;
		for (int i = 0 ; i < buffer.size(); ++i)
		{
			if (buffer[i] == 'Q' || buffer[i] == 'Z')
			{
				flag = true;
				break;
			}
			str[i] = namenum[buffer[i]-'A'];
		}
		if (flag)
			continue;
		//cout << str << endl;
		dict[buffer] = string(str);
	}
	fin >> buffer;
	bool flag = false;
	for (auto iter = dict.begin(); iter != dict.end(); ++iter )
	{
		//cout << iter->first << ' ' << iter->second << endl;
		if (iter->second == buffer)
		{
			fout << iter->first << endl;
			flag = true;
		}
	}
	if (!flag)
		fout << "NONE" << endl;


}
