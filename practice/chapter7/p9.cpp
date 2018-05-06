/* ***********************************************
Author :111qqz
mail: hust.111qqz@gmail.com
Created Time :Sun 06 May 2018 12:27:03 PM EDT
File Name :p9.cpp
************************************************ */
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
using std::string;
using std::vector;
using std::cout;
void Biasedsort(vector<string>&V){
	std::sort(V.begin(),V.end(),[](string a,string b){
							     if (a=="Me First") return true;
							     if (b=="Me First") return false;
								 return a<b;
							     });
}

int main()
{
	vector<string>vec{"Me First","hust2014","111qqz","sensetime","time to make sense","201802","shadow","Me First"};
	Biasedsort(vec);
	std::copy(vec.begin(),vec.end(),std::ostream_iterator<string>(cout,"\n"));
	return 0;
}
