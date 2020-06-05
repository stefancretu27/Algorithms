#include "array_greedy_algorithms.hpp"

/* Maximize sum of consecutive differences in a circular array/Maximum sum of absolute difference of an array
 * 
 * Problem description: Given an array of N integers it is aimed to find the maximum possible sum that can be obtained from the absolute differences of consecutive elements, including the difference between the 1st
 * 						and the last element (like a circular array).
 * 						Eg: sum = |a0-a1| + |a1-a2| + ... +|an-a0|
 * 
 * Approach: Since the sum has to have a greater as possible value it means that each absolute difference should be as big as possible. In order to maximize the differences of consecutive elements the array is firstly 
 * 			sorted in ascending order in order to better identify elements with low value s and big values, respectively. Thereafter, these values are stored in another array in an interleaving manner, such that
 * 			a min element is succeeded by a max element. Thus, the difference of 2 consecutive elements is maximized. The new array's structure would be like: a(0), a(n), a(1), a(n-1)...a(n/2-1), a(n/2).
 * 			Then simply iterate over the new array and compute de abs difference of each 2 consecutive elements. The sum can be initialize dwith abs diff of first and last elements.
 */ 

namespace max_sum_absolute_diffs
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

	void compute_sum_sorting(vector<vector<int>>& input_vectors, vector<int>& sums)
	{
		//Perform algorithm for multiple input vectors
		for(auto& vec : input_vectors)
		{
			//Step 1: sort input vector in ascending order. Use lambda for the sake of syntax. If the conditions is true, std::sort does not interchange elements
			std::function<bool(int&, int&)> cmp {[](int& lhs, int& rhs)
													{return lhs<rhs;}
												};
			sort(vec.begin(), vec.end(), cmp);
			
			//Step 2: interleave elements
			std::vector<int> interleave;
			interleave.reserve(vec.size());
			
			for(std::vector<int>::size_type idx{0}, dim = vec.size(); idx < dim/2; ++idx)
			{
				interleave.push_back(vec[idx]);
				interleave.push_back(vec[dim-idx-1]);
			}
			
			//if vec has odd number of elements, add the middle element
			if(vec.size()%2!=0)
			{
				interleave.push_back(vec[vec.size()/2]);
			}
					
			//Step 3: compute sum
			int sum = std::abs(interleave.back()-interleave.front());
			for(std::vector<int>::size_type idx{0}, dim = interleave.size()-1; idx < dim; ++idx)
			{
				sum+=std::abs(interleave[idx]-interleave[idx+1]);
			}
			sums.push_back(sum);									
		}
	}
	
	void print_sums(const std::vector<int>& sums)
	{
		//cout<<" job id "<<" deadline "<<" profit "<<" day of execution"<<endl;
		for(auto it=sums.cbegin(), end=sums.cend(); it!=end; ++it)
		{
			cout<<"Sum of abs diffs of consecutive elements for vector "<<it-sums.cbegin()+1<<" is: "<<*it<<endl;
		}
	}
}

void maxSum_absoluteDifferencesOfConsecutiveElements()
{
	std::vector<std::vector<int>> input_vectors;
	std::vector<int> sums;
	
	max_sum_absolute_diffs::read_input_vectors(input_vectors);
	max_sum_absolute_diffs::compute_sum_sorting(input_vectors, sums);
	max_sum_absolute_diffs::print_sums(sums);
	
}
