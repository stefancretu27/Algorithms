#include "array_greedy_algorithms.hpp"

/* Minimum product subset of an array
 * 
 * Problem description: Given an array of N integer values it is aimed to find the minimum possible product that can be obtained by multiplying the values in any subset of the input array.
 * 						Here the subset cand be the array itself or a single element, or any subset whose size ranges in between these 2 cases.
 * 
 * Approach: There is looked at particular cases of the input array:
 * 						- if it contains only zeroes, or one zero and the rest are positive, the result is 0. The zeroes are skipped from computing the product.
 * 						- if it contains an even number of negatives, the result would be the multiplication of all values divided by the largest negative value
 * 						- if it contains only positive values, the result is the minimum of those values
 */ 

namespace min_prod
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
		//Perform algorithm for multiple input vectors
		for(const auto& vec : input_vectors)
		{
			size_t count_zeroes = 0, count_negatives = 0;
			int product = 1, min_positive = numeric_limits<int>::max(), max_negative = numeric_limits<int>::min();

			//Step 1: iterate over the input array and compute product while skipping zeroes. Also, keep track of zeroes count and negatives count
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
				
				//if the value is positive, keep track of the minimum of all positives. In case all input values are positive, this will be returned
				if(*val > 0)
				{
					min_positive = min(min_positive, *val);
				}
				
				//add to final result all encountered values, but the zeroes
				product *= *val;
			}
			
			//Step 2: check zeroes and negatives counts and return appropiate result
			//if all values are 0, result is 0
			if(count_zeroes == vec.size())
			{
				product = 0;
			}
			//if there is no negative number, but only zeroes and positives, result is 0
			else if(count_negatives == 0 && count_zeroes > 0)
			{
				product = 0;	
			}
			//if there are only positive values, the result is the minimum of these values
			else if(count_negatives == 0 && count_zeroes == 0)
			{
				product = min_positive;	
			}
			//even number of negative values
			else if(count_negatives>0 && count_negatives%2 == 0)
			{
				product = product/max_negative;
			}
			
			//Store result for the currently processed input vector
			products.push_back(product);
		}
	}
	
	void print_products(const vector<int>& products)
	{
		//cout<<" job id "<<" deadline "<<" profit "<<" day of execution"<<endl;
		for(vector<int>::const_iterator it=products.cbegin(), end=products.cend(); it!=end; ++it)
		{
			cout<<"min product of vector "<<it-products.cbegin()+1<<" "<<*it<<endl;
		}
	}
}

void min_product_subset()
{
	std::vector<std::vector<int>> input_vectors;
	std::vector<int> result;
	
	min_prod::read_input_vectors(input_vectors);

	min_prod::compute_product(input_vectors, result);
	
	min_prod::print_products(result);
}
