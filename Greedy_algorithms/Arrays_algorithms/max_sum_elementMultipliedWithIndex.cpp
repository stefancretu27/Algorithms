#include "array_greedy_algorithms.hpp"

/* Maximize the sum of arr[i]*i
 * 
 * Problem description: Given an array of N integer values it is aimed to find the maximum possible sum thay can be obtained when multiplying each array element with its index
 * 
 * Approach: As the array's index is increasing, in order to maximize the result, it should be multiplied with the highest values in array. 
 * 			 Thus, the Greedy approach comes from the need to sort the array in ascending order and compute the sum of products.
 */ 

namespace maxSumElemIndex
{
	using namespace std;

	void read_input_vectors(vector<vector<int>>& input_vectors)
	{
		ifstream file;
		//use same input vectors as with min_prod algorithm
		file.open("min_prod.txt", ios::in);
		
		string line;
		int value;
		vector<int> temp;
		
		while(getline(file, line))
		{
			//erase previously read vector
			temp.clear();
			
			//treat each line like a stream of values, instead of string object. 
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

	void compute_max_sum(vector<vector<int>>& input_vectors, vector<int>& sums)
	{
		//Perform algorithm for multiple input vectors
		for(auto& vec : input_vectors)
		{
			int sum = 0;
			
			//Step 1: build priority queue atop if input vector
			//if cmp function's condition is true, then the elements are not interchanged
			auto cmp_less{ [](int& lhs, int& rhs){return lhs<rhs;}};
			
			sort(vec.begin(), vec.end(), cmp_less);
			
			//Step 2: compute sum of products
			for(size_t idx{0}, dim = vec.size(); idx<dim; ++idx)
			{
				sum += vec[idx]*idx;
			}
			
			//Store result for the currently processed input vector
			sums.push_back(sum);
		}
	}
	
	void print_sums(const vector<int>& sums)
	{
		for(vector<int>::const_iterator it=sums.cbegin(), end=sums.cend(); it!=end; ++it)
		{
			cout<<"max sum for vector "<<it-sums.cbegin()+1<<" "<<*it<<endl;
		}
	}
}

void max_sum_elementMultipliedWithIndex()
{
	std::vector<std::vector<int>> input_vectors;
	std::vector<int> sums;
	
	maxSumElemIndex::read_input_vectors(input_vectors);
	
	maxSumElemIndex::compute_max_sum(input_vectors, sums);
	maxSumElemIndex::print_sums(sums);
}

