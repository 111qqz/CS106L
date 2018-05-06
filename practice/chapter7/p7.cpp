/* ***********************************************
Author :111qqz
Created Time :Sun 06 May 2018 11:31:26 AM EDT
File Name :p7.cpp
************************************************ */
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <iterator> // for ostream_iterator
using std::vector;
using std::string;
using std::cout;
using std::endl;
void RemoveShortWords(vector<string>&V){
	V.erase(remove_if(V.begin(),V.end(),[](string x){return x.length()<=3;}),V.end());
}
int main()
{
	vector<string>vec{"hello","hust","yeah","sad","hha","test","yy"};
	RemoveShortWords(vec);
	std::copy(vec.begin(),vec.end(),std::ostream_iterator<string>(cout,"\n")); 

	return 0;
}
