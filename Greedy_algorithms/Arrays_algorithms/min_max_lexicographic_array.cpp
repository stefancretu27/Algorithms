#include "array_greedy_algorithms.hpp"

/* Minimum increments or decrements to make array non increasing
 * 
 * Problem description: Given an array of N integers representing digits (0<=a[i]<=9) and a positive integer K (which can be higher than array size) it is aimed to find the minimum (or the maximum) number
 * 						that can be obtained from the input array's digits given only k swaps are allowed.
 * 
 * Approach: Part 1: find min/max value: 
 * 			Iterate over the input vector (but last value) and find the minimum value in the first k elements, as k swaps are allowed. 
 * 				 - Here, if k < array.size(), then the min value is looked for only in the first k elements. 
 * 				 - If k is > array.size(), then the min value is searched for in the entire vector. After the swaps are performed, k is updated as the number of swaps is substracted from it and the algorithm is 
 * 			repeated with the new k value. At every new step, the search sub array's boundaries are adjusted, as follows:
 * 					  - as the min value was swapped on position i-1, in the previous step, the current step searches for the min value starting with i index. 
 * 					  - the end of the earch subarray is set with respect the the current index (i), as i+k. However, if i+k > arr.size(), then arr.size() is set as upper limit.
 * 			Thus, the easrhing indexes are [idx, min(arr.size(), idx + k +1). The extra + 1 is needed for pointing past last element, as size() does when ofsetting from arr.begin()
 * 			Hence, the Greedy approach looking for the best fit valueform the remaining problem domain.
 * 
 * 			Part 2: swap elements sequentially so placing the min/max value at the top
 * 			Once the minimum value was found, starting with its position, the elements are swapped till reaching the current index (i), as in swap(arr[i], ar[i-1]). At the end of this loop, the min value should be
 * 			placed on index i.
 */ 

namespace minMaxLexicographicNumber
{
	using namespace std;

	void read_input_vectors(vector<vector<unsigned>>& input_vectors, size_t& k)
	{
		ifstream file;
		file.open("minSumProdsTwoArrays.txt", ios::in);
		
		//declare string to read each line into
		string line;
		//parse each string using istringstream into the varibales declared below
		int value;
		vector<unsigned> vec, aux;
		
		//get first line separately to read k
		getline(file, line);
		istringstream is(line);
		is >> k;
		
		/*
		 * Read file line by line using getline from basic_string
		 * It returns the input stream and sets EOF flag if the case, or error flag if any error in reading the input stream occured
		 * */
		while(getline(file, line))
		{
			//clear previosuly read vector
			vec.clear();
			
			/*
			 * Treat each line like a stream of values, instead of string object. It is like dividing the whole string into substrings
			 */ 
			istringstream iss(line);

			cout<<"vector values: ";
			/*
			 * Parse the string into separate values
			 * */
			while(iss>>value)
			{
				cout<<value<<" ";
				//push the read data into the used data structure
				vec.push_back(value);
			}
			//store the vector
			input_vectors.push_back(vec);
		}

		cout<<endl;
		
		file.close();
	}

	/*
	 * For each vector in the input pair of vectors store a result formed by the number of changes. Also the vectors are modified
	 */
	void compute_minLexicograficNumber(vector<vector<unsigned>>& input_vectors, size_t& k, vector<vector<unsigned>>& result)
	{
		unsigned short count{0};
		size_t back_k{k};
		//repeat the algorithm for each input vector
		for(std::vector<unsigned>& vec : input_vectors)
		{
			++count;
			//for each input vector increase k
			k = back_k * count;
			
			//create a copy of the vector so not to modufy the input
			vector<unsigned> bak_vec(vec);

			//iterate over input vector, skipping the last element, as the min value is searched for starting with idx+1
			for(std::vector<unsigned>::size_type idx{0}, dim = bak_vec.size()-1; idx < dim && k >0; ++idx)
			{
				//Step 0: compute the upper bound of the subarray where the min value is searched for. Basically, check if there can be built the subarray with positions [idx, idx+k +1].The extra + 1 is for pointing past
				//last element. If not, upper bound is vector size  
				unsigned upper_bound = min(bak_vec.size(), idx + k + 1);
				
				//Step 1: find the iterator of the min value in the rest of the vector
				auto min_it = min_element(bak_vec.begin() + idx, bak_vec.begin() + upper_bound);
				
				//get the index of the found min value 
				size_t min_pos = min_it - bak_vec.begin();
				
				//Step 2: perform swaps starting with min_pos towards current idx. Thus, the total number of swap done in this steps is min_pos-idx, as this is the subarray whose values are swapped
				for(size_t idy = min_pos; idy >idx; --idy)
				{
					std::swap(bak_vec[idy], bak_vec[idy-1]);
				}
				
				//Step 3: update value of k
				k -= min_pos -idx;
			}
			
			result.push_back(bak_vec);
			bak_vec.clear();
		}
	}
	
	void compute_maxLexicograficNumber(vector<vector<unsigned>>& input_vectors, size_t& k, vector<vector<unsigned>>& result)
	{
		unsigned short count{0};
		size_t back_k{k};
		//repeat the algorithm for each input vector
		for(std::vector<unsigned>& vec : input_vectors)
		{
			++count;
			//for each input vector increase k
			k = back_k * count;
			
			//create a copy of the vector so not to modufy the input
			vector<unsigned> bak_vec(vec);

			//iterate over input vector, skipping the last element, as the min value is searched for starting with idx+1
			for(std::vector<unsigned>::size_type idx{0}, dim = bak_vec.size()-1; idx < dim && k >0; ++idx)
			{
				//Step 0: compute the upper bound of the subarray where the min value is searched for. Basically, check if there can be built the subarray with positions [idx, idx+k +1]. The extra + 1 is for pointing past
				//last element. If not, upper bound is vector size 
				unsigned upper_bound = min(bak_vec.size(), idx + k + 1);
				
				//Step 1: find the iterator of the max value in the rest of the vector
				auto max_it = max_element(bak_vec.begin() + idx, bak_vec.begin() + upper_bound);
				
				//get the index of the found min value 
				size_t max_pos = max_it - bak_vec.begin();
				
				//Step 2: perform swaps starting with min_pos towards current idx. Thus, the total number of swap done in this steps is min_pos-idx, as this is the subarray whose values are swapped
				for(size_t idy = max_pos; idy >idx; --idy)
				{
					std::swap(bak_vec[idy], bak_vec[idy-1]);
				}
				
				//Step 3: update value of k
				k -= max_pos - idx;
			}
			
			result.push_back(bak_vec);
			bak_vec.clear();
		}
	}
	
	void print_result(const vector<vector<unsigned>>& result)
	{
		for(auto& vec : result)
		{
			cout<<"Changed vector"<<endl;
			for(std::vector<unsigned>::const_iterator it = vec.begin(), end = vec.end(); it!=end; ++it)
			{
				cout<<*it;
			}
			cout<<endl;
		}
	}
}

void min_max_lexicographic_number()
{
	std::vector<std::vector<unsigned>> input_vectors, result;
	size_t k;
	
	minMaxLexicographicNumber::read_input_vectors(input_vectors, k);
	minMaxLexicographicNumber::compute_minLexicograficNumber(input_vectors, k, result);
	std::cout<<"Min number"<<std::endl;
	minMaxLexicographicNumber::print_result(result);
	
	result.clear();
	minMaxLexicographicNumber::compute_maxLexicograficNumber(input_vectors, k, result);
	std::cout<<"Max number"<<std::endl;
	minMaxLexicographicNumber::print_result(result);
	
}
