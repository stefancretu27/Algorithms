#include "array_greedy_algorithms.hpp"

/* Minimum changes to make array's GCD multiple of k
 * 
 * Problem description: Given an array of N positive integers and a positive integer k, it is aimed to find minimum increments/decrements by 1 to make array's elements' greatest common divisor to be k.
 * 
 * Approach: The values are compared to k:
 * 				- those smaller than k are treated separately, as there is needed to add the difference between k and eahc of these values <=> ceil by k-arr[idx]
 * 				- those higher than k can be ceiled or floored by minimum value of arr[idx]%k and k-arr[idx]%k. If arr[idx]<=k/2 => arr[idx]-=arr[idx]%k; Else arr[idx] += k-arr[idx]%k
 * 
 */ 			 

namespace minChanges_GCD_k_Multiple
{
	using namespace std;

	void read_input_vectors(vector<vector<unsigned>>& input_vectors, unsigned& k)
	{
		ifstream file;
		file.open("minSumProdsTwoArrays.txt", ios::in);
		
		//declare string to read each line into
		string line;
		//parse each string using istringstream into the varibales declared below
		int value;
		vector<unsigned> vec;
		
		//get first line separately to read k. For convenience, k is the same for all vectors
		getline(file, line);
		istringstream is(line);
		is >> k;
		
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
	void compute_minChangesGCD(vector<vector<unsigned>>& input_vectors, const unsigned &k, vector<size_t>& v_changes)
	{
		for(std::vector<unsigned>& vec : input_vectors)
		{
			size_t changes{0};
			for(std::vector<unsigned>::iterator it = vec.begin(), end = vec.end(); it!=end; ++it)
			{
				//Step 1: all values smaller than k are ceiled by k%val. This also is equivalent to ceiling by k-val. Even more, all values smaller than k are assigned the value of k.
				if(*it < k)
				{
					changes += k-*it;
					*it = k;
				}
				// Step 2: treat values higher than k
				else if (*it > k)
				{
					//find remainder
					unsigned remainder  = *it%k;
					
					//process only the values which are not multiple of k
					if(remainder)
					{
						//apply smalles change. If remiander is smaller than half k, means the value is closer to a multiple of k which is smaller than the value
						if(remainder <= k/2)
						{
							changes += remainder;
							*it -= remainder;
						}
						//if the remainder is higher than half of k it means the value is closer to a multiple of k which is higher than the value
						else
						{
							changes += k-remainder;
							*it +=k-remainder;
						}
					}
				}
			}
			v_changes.push_back(changes);
		}
	}
	
	void print_result(const vector<vector<unsigned>>& input_vectors, const std::vector<size_t>& changes)
	{
		size_t idx{0};
		for(auto& vec : input_vectors)
		{
			cout<<"Changed vector"<<endl;
			for(std::vector<unsigned>::const_iterator it = vec.begin(), end = vec.end(); it!=end; ++it)
			{
				cout<<*it<<" ";
			}
			cout<<"changes: "<<changes[idx++]<<endl;
		}
	}
}

void minChangesGCDMultipleOfK()
{
	std::vector<std::vector<unsigned>> input_vectors;
	unsigned k;
	std::vector<size_t> changes;
	
	minChanges_GCD_k_Multiple::read_input_vectors(input_vectors, k);
	minChanges_GCD_k_Multiple::compute_minChangesGCD(input_vectors, k, changes);
	minChanges_GCD_k_Multiple::print_result(input_vectors, changes);
	
}
