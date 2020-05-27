#include "array_greedy_algorithms.hpp"

/*
 * Problem description: Given an array of N integer values it is aimed to find the maximum possible sum thay can be obtained when adding all array elements after k of them are negated. 0<k<N.
 * Approach: As the array's element can have negative, positive and zero values, the maximum sum can be obtained if the first minimum k elements are negated. Concretely, the zeroes will stay as they are while
 * 			the negative numbers are turned positive. If the number of negatives is < k, then the zeroes are considered. If still k values were not reached, then the smallest positives are turned negative.
 */ 

namespace maxSumKNeg
{
	using namespace std;

	void read_input_vectors(vector<pair<vector<int>, unsigned>>& input_vectors)
	{
		ifstream file;
		file.open("max_sum_Knegations.txt", ios::in);
		
		string line;
		int value, k;
		vector<int> temp;
		
		while(getline(file, line))
		{
			//erase previously read vector
			temp.clear();
			
			//treat each line like a stream of values, instead of string object. 
			istringstream iss(line);
			
			//First element on the line represents the value of k
			iss>>k;
			
			cout<<"vector values: ";
			//parse the string into integers
			while(iss>>value)
			{
				cout<<value<<" ";
				//push the read data into the used data structure
				temp.push_back(value);
			}
			cout<<endl;
			input_vectors.push_back(make_pair(temp, k));
		}
		
		file.close();
	}

	void compute_max_sum(vector<pair<vector<int>, unsigned>>& input_vectors, vector<pair<int, unsigned>>& sums)
	{
		for(auto& vec_pair : input_vectors)
		{
			unsigned k = vec_pair.second;
			int sum = 0;
			
			//Step 1: build priority queue atop if input vector
			//if cmp function's condition is true, then the elements are interchanged
			function<bool(int, int)> cmp_greater{[](int x, int y){return x > y;}};
			
			priority_queue<int, vector<int>, function<bool(int, int)>> prio_queue(cmp_greater);
			//add vector to queue
			for(int elem : vec_pair.first)
				prio_queue.push(elem);
			
			for(unsigned idx = 0; idx <k; ++idx)
			{
				sum -= prio_queue.top();
				prio_queue.pop();
			}
			for(unsigned idx = k, dim = vec_pair.first.size(); idx < dim; ++idx)
			{
				sum += prio_queue.top();
				prio_queue.pop();
			}
			
			sums.push_back(make_pair(sum, k));
		}
	}
	
	void print_sums(const vector<pair<int, unsigned>>& sums)
	{
		for(vector<pair<int, unsigned>>::const_iterator it=sums.cbegin(), end=sums.cend(); it!=end; ++it)
		{
			cout<<"max sum for vector "<<it-sums.cbegin()+1<<" "<<it->first<<" after negations: "<<it->second<<endl;
		}
	}
}

void max_sum_k_negations()
{
	std::vector<std::pair<std::vector<int>, unsigned>> input_vectors;
	std::vector<std::pair<int, unsigned>> sums;
	
	maxSumKNeg::read_input_vectors(input_vectors);
	
	maxSumKNeg::compute_max_sum(input_vectors, sums);
	maxSumKNeg::print_sums(sums);
}
