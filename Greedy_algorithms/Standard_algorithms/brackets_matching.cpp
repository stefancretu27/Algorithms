#include "standard_greedy_algorithms.hpp"

/*
 * Problem description: Given an input string containing an equal number of open and closed brackets in a random order ( '[] and ']') it is aimed at finding the minimum number of permutation that would lead to a balanced     *						string, namely all brackets are matching (as in maths)
 * 
 * Approach: A naive approach would entail a O(n^2) complexity:
 *				 - This involves iterating over the input string whilst keeping an integer brackets_counter which is incremented when an '[' is met and decremented when an ']' is met.
 * 				 - When the brackets_counter becomes negative, it means there are more cloed brackets than open ones, till the cuurent index. Thus, a swap is required.
 *				 - For performing a swap, an inner loop searches from the current_index+1 for the first open bracket. When found, the swap is performed and the brackets_counter is set to 1 because, at the current index an      	* 				   open bracket can be found now. Also, break form the inner loop and continue with the outer loop.
 *
 *			A better approach comes with a O(n) complexity, as insetad of 2 nested loops, it uses 2 separated loops, executed sequentially:
 *				 - first loop iterates over the input string aiming to store all [ brackets' positions in an array. Let's call it open_brackets_positions and its size will be half of the input array's size
 *               -  the 2nd loops also iterates over the input string from the begging and maintains the brackets_counter as it is proceeded in the naive approach. Besides, it also maintains a counter, which is used for
 *        		 	indexing the open_brackets_positions array. This index will always indicate the next open bracket position that can be used when swapping. This index is incremented when a '[' is met while iterating and
 *			 		when swapping.
 *				 - as it is done in the naive approach, the swap is performed when the brackets_counter turn negative. After swapping, this counter is set to 1, likewise the nive approach does. 
 * 				 - both approaches use swap_counter that is incremented when swapping							
 */ 

namespace brackets
{
	using namespace std;

	//there are read more strings of brackets, so store them in a vector
	void read_input_strings(vector<string>& brackets_array)
	{
		ifstream file;
		file.open("brackets.txt", ios::in);
		
		string line;
		while(getline(file, line))
		{
			brackets_array.push_back(line);
		}
		
		file.close();
	}

	void process_strings(vector<string>& brackets_array, vector<unsigned>& swaps)
	{
		//process each input string
		for(string& brackets_string : brackets_array)
		{
			vector<size_t> open_brackets_indexes;
			//this can be negative
			int  brackets_counter = 0;
			size_t open_bracket_index = 0;
			size_t swaps_counter = 0;
			
			cout<<"Currently processing: "<<brackets_string<<endl;
			//Step 1: iterate over brackets string to get positions of all [ brackets => eliminate O(n^2) complexity
			for(size_t idx=0, size = brackets_string.size(); idx<size; ++idx)
			{
				//when an open bracket is encountered, store its position from input string into open_brackets_idx vector
				if(brackets_string[idx]=='[')
				{
					open_brackets_indexes.push_back(idx);
				}	
			}
			
			/*
			 * Step 2: iterate over brackets string and increment brackets_counter when [ and decrement when ]
			 * 		   When brackets_counter is < 0, swap the ] bracket at the current index with the next [ bracket
			 * 		   While iterating, also increment an index when a [ bracket is met. It is used to index the open brackets vector of indexes. At any current index in input array, this index will indicate the next
			 * 			open bracket position index.
			 */
			for(size_t idx=0, size = brackets_string.size(); idx<size; ++idx)
			{
				//when an open bracket is encountered, store its position from input string into open_brackets_idx vector
				if(brackets_string[idx]=='[')
				{
					++brackets_counter;
					//move forward in open_brackets_indexes vector
					++open_bracket_index;
				}
				
				if(brackets_string[idx]==']')
				{
					--brackets_counter;
				}
				
				//when the counter is negative, it means a swap has to be done, as there is ] one too many
				if(brackets_counter < 0)
				{
					//perform swapping
					swap(brackets_string[idx], brackets_string[open_brackets_indexes[open_bracket_index]]);
					
					//move forward in open_brackets_indexes vector
					++open_bracket_index;
		
					//mark the fact that at the current index is a [ and not a ] anymore
					brackets_counter = 1;
					
					//mark that a swap has been done
					++swaps_counter;
				}
			}
			
			swaps.push_back(swaps_counter);
		}
	}

	void print_ordered_strings(vector<string>& brackets_array, vector<unsigned>& swaps)
	{
		cout<<"ordered brackets string              number of needed swaps"<<endl;
		for(size_t idx=0, size = brackets_array.size(); idx<size; ++idx)
		{
			cout<<brackets_array[idx]<<"                     "<<swaps[idx]<<endl;
		}
	}
}

void brackets_swapping()
{
	std::vector<std::string> brackets_array;
	std::vector<unsigned> swaps;
	
	brackets::read_input_strings(brackets_array);

	brackets::process_strings(brackets_array, swaps);
	
	brackets::print_ordered_strings(brackets_array, swaps);
}
