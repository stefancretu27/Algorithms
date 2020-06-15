#include "array_greedy_algorithms.hpp"

/* Minimum sum by choosing min value from pairs from array
 * 
 * Problem description: Given an array of N integer values it is aimed to find the minimum possible sum that can be obtained by always choosing the min value when formin pairs of elemnts from the array.
 *						When choosing the min value, the other value is removed from array. The process continues untill input array has one element.
 * 
 * Approach: The trick here is that the min value always stays within the array. Thus, once the min value in the array is found, at each step it will be kept such that at the end it will be the only element in array.
 *			 At each iteration, the the min value is also chosen and pushed into another array. At the end, this secondary array will contain the min value n-1 times. That said, the minimum sum from min value from pairs 
 *			 would be min value times size of the array-1. Thus, a shorter implementation would be to find the min value and multiplie it by size-1. 
 *
 * Problem description 2: Similarly as above but at each step the min value will not stay into array, but is is only pushed in the secondary array.
 * Approach 2: This implies that at each iteration, the newly formed pair has a new min value. At the end, the secondary array will have size/2 values. However, if size is an even number, the algorithm stops when
 *				the input array's size becomes 0. If size is an odd number, the algorithm stops when the input array has one element. This implies sorting the input array ascending and considering for summation the
 * 				first size/2 elements.
 */ 

namespace minSum_MinValueFromPairs
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

	void compute_minSum_MinValuesFromPairs(vector<vector<int>>& input_vectors, vector<int>& sums)
	{
		//Perform algorithm for multiple input vectors
		for(auto& vec : input_vectors)
		{
			//Step 1: sort input in ascending order 
			std::function<bool(const int&, const int &)> cmp_less{[](const int &lhs, const int &rhs){return lhs<rhs;}};
			
			sort(vec.begin(), vec.end(), cmp_less);
				
			int sum{0};
			//Step 2: summation of 1st half of the pqueue
			for(std::vector<int>::size_type idx{0}, half_dim = vec.size()/2; idx < half_dim; ++idx)
				sum+=vec[idx];
			
			//Store result for the currently processed input vector
			sums.push_back(sum);
		}
	}
	
	void print_sums(const vector<int>& sums)
	{
		//cout<<" job id "<<" deadline "<<" profit "<<" day of execution"<<endl;
		for(vector<int>::const_iterator it=sums.cbegin(), end=sums.cend(); it!=end; ++it)
		{
			cout<<"min sum from min values from pairs of vector "<<it-sums.cbegin()+1<<" "<<*it<<endl;
		}
	}
}

void minSumFromMinValueOfPairs()
{
	std::vector<std::vector<int>> input_vectors;
	std::vector<int> result;
	
	minSum_MinValueFromPairs::read_input_vectors(input_vectors);

	minSum_MinValueFromPairs::compute_minSum_MinValuesFromPairs(input_vectors, result);
	
	minSum_MinValueFromPairs::print_sums(result);
}
