#include "standard_greedy_algorithms.hpp"

/*
 * Given a fraction (numerator/denominator) it should be wriiten as a sum of unique unit fractions (1/x +1/y +1/z etc)
 * Approach: If the input fraction's denominator divides exactly the numerator (4/2), then it is not a fraction and the division result is returned.
 * 			 If numerator or denominator are 0, 0 is returned.
 * 			 If numerator is greater than denominator, firstly is written the inetegr result of the division, then it is proceeded further with the remaining fraction which becomes the new input fraction.
 * 			 If numerator is already 1 and denominator is >1, then return this fraction.
 * 			 If none of the above cases, then the algorithm begins. 
 * 				Firstly, a subunitary fraction (a/b), if reversed (b/a) becomes supraunitary. 
 * 				By performing the division of the latter it is obtained a value (c) which is not necessarily an integer. However, if reversed (1/c) represents the result of the division of a/b (or a/b is obtained again).
 * 				Following this approach, if instead of considering c, is taken into account the upper bound integer of c (let's name it L) then it would represent the integer superior limit of reversed input fraction b/a. 
 * 				Nonetheless, if reversed (1/L), then it would represent the inferior limit of input fraction a/b. Thus, it is obtained each unique unit fraction.
 * 				Then, it is proceeded similarily for the remainder (a/b -1/L) => recursion
 */

using namespace std;

string process_fraction(pair<int,int>& fraction)
{
	if(fraction.second == 0)
	{
		return "invalid fraction";
	}
	
	if(fraction.first == 0)
	{
		return "numerator is 0";
	}
	
	static string result;
	//if numerator is divided exactly by denominator (4/2), then it is not a fraction. So return the result of the division. Also, here numerator >denominator (supraunitary)
	if((fraction.first%fraction.second) == 0)
	{
		return to_string(fraction.first/fraction.second);
	}
	
	//if denominator is divided by numerator (2/4), then the fraction can be written as unitary unqie one (1/2). Here, clearly it is a subunitary fraction. Also, this marks the end of recursion
	if( (fraction.second%fraction.first) == 0)
	{
		result += "1/" + to_string(fraction.second/fraction.first);
		return result;
	}
	
	//if it is a supraunitary fraction, but numerator or denominator do not divide each other, then append the integer part of the division's result and proceed further with the subunitary one
	if(fraction.first > fraction.second)
	{
		int res = fraction.first/fraction.second;
		result += to_string(res) + " + ";
		
		pair<int,int> rest_fraction = make_pair(fraction.first%fraction.second, fraction.second);
		return process_fraction(rest_fraction);
	}
	
	//Once the processing got here, clearly it deals only with subunitary non-dividable fractions
	
	//Step 1: reverse input fraction and ceil the result (add 1 to the integer result of division) to obtain the upper bound of the reversed fraction
	int ceiling = 1 + fraction.second/fraction.first;
	//Step 2: revert back the input fraction and the ceiling. Thus, the former upper bound becomes a lower bound which has the seeked form of unique unitary fraction (1/ceiling)
	result += "1/" + to_string(ceiling) + " + ";
	
	//Step 3: the lower
	pair<int, int> remaining_fraction;
	remaining_fraction.second = fraction.second*ceiling;
	remaining_fraction.first = fraction.first*ceiling-fraction.second;
	
	return process_fraction(remaining_fraction);
}

void egyptian_fraction()
{
	pair<int,int> fraction;
	cout<<"numerator: "<<endl;
	cin>>fraction.first;
	cout<<"denominator: "<<endl;
	cin>>fraction.second;
	
	cout<<"The fraction is "<<fraction.first<<"/"<<fraction.second<<endl;
	
	cout<<process_fraction(fraction)<<endl;
}
