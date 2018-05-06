/* ***********************************************
Author :111qqz
mail: hust.111qqz@gmail.com
Created Time :Sun 06 May 2018 11:55:53 AM EDT
File Name :p6.cpp
************************************************ */
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using std::vector;
using std::cout;
using std::endl;
using std::lower_bound;
int main()
{
	vector<int>vec{4,15,25,31,23,56,78,32,56,43,36,73};
	//25 + 31 + 56 + 32 + 56 + 43 + 36 + 73 = 352;
	// 352/8 = 44;
	std::sort(vec.begin(),vec.end());
	auto it = lower_bound(vec.begin(),vec.end(),25);
	auto it2 = lower_bound(vec.begin(),vec.end(),75);
	if (it!=vec.end()&&it2!=vec.end()){
		cout<<std::accumulate(it,it2,0.0)/std::distance(it,it2)<<endl;
	}else{
		cout<<" no value between 25 and 75"<<endl;
	}
	return 0;
}
