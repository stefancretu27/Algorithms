#include "array_greedy_algorithms.hpp"

/*
 * Problem description: Given an array of integer values it is aimed to find the maximum possible product that can be obtained by multiplying the values in any subset of the input array.
 * 						Here the subset cand be the array itself or a single element, or any subset whose size ranges in between these 2 cases.
 * Approach: There is looked at particular cases of the input array:
 * 						- if it contains only zeroes, or one negataive and the rest are zeroes, the result is 0. The zeroes are skipped from computing the product
 * 						- if it contains an odd number of negatives, the result would be the multiplication of all values divided by the largest negative value
 */ 

namespace max_prod
{
	using namespace std;

	void read_input_vectors(vector<vector<int>>& input_vectors)
	{
		ifstream file;
		file.open("min_prod.txt", ios::in);
		
		string line;
		int value;
		vector<int> temp;
		
		while(getline(file, line))
		{
			//erase previously read vector
			temp.clear();
			
			//treat each line like a stream of values, instead of string object
			istringstream iss(line);
			
			cout<<"vector values: ";
			//parse the string into integers
			while(iss>>value)
			{
				cout<<value<<" ";
				//push the read data into the used data structure
				temp.push_back(value);
			}
			cout<<endl;
			input_vectors.push_back(temp);
		}
		
		file.close();
	}

	void compute_product(const vector<vector<int>>& input_vectors, vector<int>& products)
	{
		for(const auto& vec : input_vectors)
		{
			size_t count_zeroes = 0, count_negatives = 0;
			int product = 1, max_negative = numeric_limits<int>::min();

			//Step 1: iterate over the input array
			for(vector<int>::const_iterator val = vec.cbegin(), dim = vec.cend(); val!=dim; ++val)
			{
				//when a 0 is met, skip it and increment counter
				if(*val == 0)
				{
					++count_zeroes;
					continue;
				}
				
				//if the value is negative, keep track of the maximum of all negatives. In case of even number of negative values, the final result will be product of all values divided by this max_negative
				//also, count the number of negatives
				if(*val < 0)
				{
					++count_negatives;
					max_negative = max(max_negative, *val);
				}
				
				//add to final result all encountered values, but the zeroes
				product *= *val;
			}
			
			//if all values are 0, result is 0
			if(count_zeroes == vec.size())
			{
				product = 0;
			}
			//if there is only one negative number, and the rest are zeroes, result is 0
			else if(count_negatives == 1 && count_zeroes == vec.size()-1)
			{
				product = 0;	
			}
			//odd number of negative values, the result is divided by max negative, so a positive value is retrieved
			else if(count_negatives>0 && count_negatives%2 == 1)
			{
				product = product/max_negative;
			}
			
			cout<<product<<endl;
			products.push_back(product);
		}
	}
	
	void print_products(const vector<int>& products)
	{
		//cout<<" job id "<<" deadline "<<" profit "<<" day of execution"<<endl;
		for(vector<int>::const_iterator it=products.cbegin(), end=products.cend(); it!=end; ++it)
		{
			cout<<"max product of vector "<<it-products.cbegin()+1<<" "<<*it<<endl;
		}
	}
}

void max_product_subset()
{
	std::vector<std::vector<int>> input_vectors;
	std::vector<int> result;
	
	max_prod::read_input_vectors(input_vectors);

	max_prod::compute_product(input_vectors, result);
	
	//max_prod::print_products(result);
}
