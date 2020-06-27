#include "array_greedy_algorithms.hpp"

/* Minimum increments or decrements to make array non increasing
 * 
 * Problem description: Given an array of N integers it is aimed to find min number of increase/decrease by 1 to make array non increasing.
 * 
 * Approach: The tip here is to treat the first value separately, as it is changed only of the next value is higher than it. Also, the last value is treated separately, bot only after al previous values had been changed.
 * 			It is compared just to the second to last value. 
 * 			The values in between are changed within a loop, as follows: 
 * 				- if the current value is higher than its prev, just make it equal to prev, regardless of the next value. So, at any given moment, the current and the prev respect the non increasing requirement
 * 				- if the current value is lower than prev and lower than next, make it equal to minimum between prev and next
 * 			The Greedy approach comes from the fact that the change is applied to the current value (as early as possible).
 */ 

namespace minInc_Dec_nonIncreasingArray
{
	using namespace std;

	void read_input_vectors(vector<vector<int>>& input_vectors)
	{
		ifstream file;
		file.open("minSumProdsTwoArrays.txt", ios::in);
		
		//declare string to read each line into
		string line;
		//parse each string using istringstream into the varibales declared below
		int value;
		vector<int> vec, aux;
		
		//get first line separately to read k
		getline(file, line);
		istringstream is(line);
		is >> value;
		
		/*
		 * Read file line by line using getline from basic_string
		 * It returns the input stream and sets EOF flag if the case, or error flag if any error in reading the input stream occured
		 * */
		while(getline(file, line))
		{
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
	void compute_minChanges(vector<vector<int>>& input_vectors, vector<size_t>& result)
	{
		for(std::vector<int>& vec : input_vectors)
		{
			size_t no_of_changes{0};
			
			//Step 1: check first value
			if(vec[0] < vec[1])
			{
				//compute number of changes
				no_of_changes += vec[1]- vec.front();
				//then change value: make the front value equal to the enxt one for min changes
				vec[0] = vec[1];
				
			}
			
			
			//Step 2: change values in between front and back
			for(std::vector<int>::size_type idx{1}, dim = vec.size()-1; idx < dim; ++idx)
			{
				//if current is higher than prev, make it equal to prev
				if(vec[idx] > vec[idx -1])
				{
					no_of_changes += vec[idx] - vec[idx-1];
					vec[idx] = vec[idx-1];
				}
				//if current is lower than prev (this respects the requirement) and lower than next, change it to min of prev and next
				else if(vec[idx] < vec[idx -1] && vec[idx] < vec[idx+1])
				{
					int min_val = min(vec[idx-1], vec[idx+1]);
					no_of_changes += abs(min_val-vec[idx]);
					vec[idx] = min_val;
				}
			}
			
			//Step 3: check last value
			if(vec.back() > vec[vec.size()-2])
			{
				//update number of changes
				no_of_changes += vec.back()-vec[vec.size()-2];
				//last value becomes equal to the second to last value for min changes
				vec.back() = vec[vec.size()-2];
			}
			
			result.push_back(no_of_changes);
		}
	}
	
	void print_result(const vector<vector<int>>& input_vectors, const vector<size_t>& result)
	{
		size_t idx{0};
		for(auto& vec : input_vectors)
		{
			cout<<"Changed vector"<<endl;
			for(std::vector<int>::const_iterator it = vec.begin(), end = vec.end(); it!=end; ++it)
			{
				cout<<*it<<" ";
			}
			cout<<endl<<"Changes: "<<result[idx++]<<endl;
		}
	}
}

void minChangesNonIncreasingArray()
{
	std::vector<std::vector<int>> input_vectors;
	std::vector<size_t> result;
	
	minInc_Dec_nonIncreasingArray::read_input_vectors(input_vectors);
	minInc_Dec_nonIncreasingArray::compute_minChanges(input_vectors, result);
	minInc_Dec_nonIncreasingArray::print_result(input_vectors, result);
	
}
