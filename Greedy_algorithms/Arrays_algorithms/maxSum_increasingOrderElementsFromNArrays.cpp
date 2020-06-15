#include "array_greedy_algorithms.hpp"

/* Maximum sum of increasing order elements from n arrays
 * 
 * Problem description: Given M arrays with N integers each, it is aimed to find the maximum possible sum that can be computed by selecting one item from each array, 
 * 						with i-th element being greater than the i-1 th element.
 * 
 * Approach: The Greedy approach makes use of seelcting max possible value from each vector. For this, there can be 2 strategies:
 * 				 - sort each vector. If sorted ascending, take maximum for last, then reverse iterate over the next ones, starting with seocnd last vector, and find first value smaller than previously selected one
 *               - compute maximum for each vector. When finding a max for a given vector, but the 1st, it should be verified if the newly found max value is greater than i-1 th, or smaller than i+1 th
 * 			Also, the Greedy approach is used once again as it is started with the last vector in order to increase chances to accomplish the result. If started from the first, it is possible to select a max value
 * 			which would be greater than the maximum value of the next vectors and the result would be 0. The idea is to ry to cover all vectors.
 */ 

namespace max_sum_increasing_order_elements
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

	void compute_sum_sorting(vector<vector<int>>& input_vectors, vector<pair<int, size_t>>& selected_items, int& sum)
	{
		//Step 1: sort all vectors in ascending order: O(M*N*LogN) complexity
		for(auto& vec : input_vectors)
		{
			//implemented lambda for the sake of syntax. If the condition is true, the elements are not interchanged, unlike cmp function used by priority_queue
			function<bool(const int&, const int&)> cmp_lambda{[](const int& lhs, const int& rhs)
																	{return lhs<rhs;}
															 };
															 
			//O(NLogN)
			sort(vec.begin(), vec.end(), cmp_lambda);
		}
		
		//Step 2: select last element from the last vector.Pair contains the maximum value in vector and the index of the vector in the input_vectors 
		selected_items.push_back(make_pair(input_vectors.back().back(), input_vectors.size()));
		
		//Step 3: start iterating over the vector of vectors in reverse order. Also, each vector is iterated over in reverse order. Start with second last vector
		//time complexity O(M*N)
		for(auto out_it = input_vectors.crbegin()+1, out_rend = input_vectors.crend(); out_it!= out_rend; ++out_it)
		{
			for(auto in_it = out_it->crbegin(), in_rend = out_it->crend(); in_it != in_rend; ++in_it)
			{
				//while reverse iterating, find the first element smaller than the last selected one. When found, push it to the vector and break from inner loop to proceed next to outer loop
				if(*in_it<selected_items.back().first)
				{
					//when using pointer airthmetics with reverse iterators, the logic behind seems to be identic with forward iterators one, as in rbegin() < rend().
					selected_items.push_back(make_pair(*in_it, out_rend-out_it));
					break;
				}
			}
		}
		
		//Step 4: compute sum if the selected items vector size matches the number of vectors
		if(selected_items.size() == input_vectors.size())
		{
			for(auto it = selected_items.cbegin(), end = selected_items.cend(); it!=end; ++it)
			{
				sum += it->first;
			} 
		} 
	}
	
	void compute_sum_max(vector<vector<int>>& input_vectors, vector<pair<int, size_t>>& selected_items, int& sum)
	{
		int max = numeric_limits<int>::min();
		
		//Step 1: process the last vector separately. Find its max value and add it to selected items
		for(auto in_it = input_vectors.back().crbegin(), in_rend = input_vectors.back().crend(); in_it != in_rend; ++in_it)
		{
			//while reverse iterating, compute the maximum value
			if(*in_it > max)
			{
				max = *in_it;
			}
		}
		
		selected_items.push_back(make_pair(max, input_vectors.size()));		
		
		//Step 2: start iterating over the vector of vectors in reverse order. Also, each vector is iterated over in reverse order. The last vector is not processed here, as it has been done above.
		//time complexity O(M*N)
		for(auto out_it = input_vectors.crbegin()+1, out_rend = input_vectors.crend(); out_it!= out_rend; ++out_it)
		{
			//reset max for each vector
			max = numeric_limits<int>::min();
			
			//while reverse iterating, compute the maximum for each vector while keeping track if it is lower than last selected item
			for(auto in_it = out_it->crbegin(), in_rend = out_it->crend(); in_it != in_rend; ++in_it)
			{
				if(*in_it > max && *in_it<selected_items.back().first)
				{
					max = *in_it;
				}
			}
			//Select the max after iteration over vector has finished
			//when using pointer airthmetics with reverse iterators, the logic behind seems to be identic with forward iterators one, as in rbegin() < rend().
			if(max!=numeric_limits<int>::min())
				selected_items.push_back(make_pair(max, out_rend-out_it));
		}
		
		//Step 3: compute sum if the selected items vector size matches the number of vectors
		if(selected_items.size() == input_vectors.size())
		{
			for(auto it = selected_items.cbegin(), end = selected_items.cend(); it!=end; ++it)
			{
				sum += it->first;
			} 
		} 
	}
	
	void print_selected_elements(const std::vector<std::pair<int, size_t>>& selected_elements, const int& sum)
	{
		//cout<<" job id "<<" deadline "<<" profit "<<" day of execution"<<endl;
		for(auto it=selected_elements.cbegin(), end=selected_elements.cend(); it!=end; ++it)
		{
			cout<<"selected items from vector "<<it->second<<" is: "<<it->first<<endl;
		}
		
		cout<<"Sum is: "<<sum<<endl;
	}
}

void maxSum_increasingOrderElementsFromNArrays()
{
	std::vector<std::vector<int>> input_vectors;
	std::vector<std::pair<int, size_t>> selected_elements;
	int result{0};
	
	max_sum_increasing_order_elements::read_input_vectors(input_vectors);

	max_sum_increasing_order_elements::compute_sum_sorting(input_vectors, selected_elements, result);
	max_sum_increasing_order_elements::print_selected_elements(selected_elements, result);
	
	selected_elements.clear();
	result = 0;
	max_sum_increasing_order_elements::compute_sum_max(input_vectors, selected_elements, result);
	max_sum_increasing_order_elements::print_selected_elements(selected_elements, result);
}
