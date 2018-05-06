/* ***********************************************
Author :111qqz
mail: hust.111qqz@gmail.com
Created Time :Sun 06 May 2018 12:16:03 PM EDT
File Name :p8.cpp
************************************************ */
#include <vector>
#include <numeric>
#include <iostream>
using std::vector;
using std::endl;
using std::cout;

double DistanceToOrigin(vector<double>& V){
	return std::inner_product(V.begin(),V.end(),V.begin(),0);
}
int main()
{
	vector<double>vec{1.0,2.0,3.0,-5.0};
	cout <<  DistanceToOrigin(vec) << endl;
	return 0 ;
}

