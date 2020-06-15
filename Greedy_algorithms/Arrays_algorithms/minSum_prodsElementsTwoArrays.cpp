#include "array_greedy_algorithms.hpp"

/* Find min sum of the products between each 2 elements residing on same index from 2 arrays. It is allowed to alter the elements from the 1st array by +2 or -2, k times
 * 
 * Problem description: Given 2 arrays of N integers each, it is aimed to find the min value for the sum = a[i]*b[i], 0<=i<N, as it is allowed to modify a[i] by +2 or -2, k times. 
 * 
 * Approach: The tip here is that only one element a[i] is to be changed k times in order to minimize the afferent product and, implicitly, the sum. 
 * 			In order to discover which a[i] should be changed, it is iterated over the vector and the default sum of products is computed. As at each iteration, the default product is computed, it is also computed the 
 * 			altered product, with the corresponding a[i] being altered accordingly. Each time is computed the difference between the default product and the altered product as absolute value. At the end, the maximum 
 * 			difference is substracted from the default sum of products yielding the targeted minimum sum. For simplicity, each altered product is pushed to a priority queue whose top will give, at the end, the max 
 *			difference.
 * 			In order to determine whether to alter a[i] by +2*k or by -2*k, it is looked at the signs of a[i] and b[i]. If a[i] > and b[i] > 0, the product is positive so a[i] is altered by -2*k. If a[i] <0 and b[i] >0
 * 			the product is negative, but it can be further minimized if a[i] is altered by -2*k. So, it is proceeded for the other 2 cases where the alteration entails +2*k.
 */ 

namespace minSum_prodsElements
{
	using namespace std;

	void read_input_vectors(pair<vector<int>, vector<int>>& input_vectors, unsigned&k)
	{
		ifstream file;
		file.open("minSumProdsTwoArrays.txt", ios::in);
		
		string line;
		int value;
		vector<int> vec, aux;
		
		//get first line separately to read k
		getline(file, line);
		istringstream is(line);
		is >> k;
		
		while(getline(file, line))
		{
			vec.clear();
			
			//treat each line like a stream of values, instead of string object. 
			istringstream iss(line);

			cout<<"vector values: ";
			//parse the string into integers
			while(iss>>value)
			{
				cout<<value<<" ";
				//push the read data into the used data structure
				vec.push_back(value);
			}
			//store the 1st vector in aux
			if(aux.empty())
				aux = vec;
		}
		
		input_vectors = make_pair(aux, vec);
		cout<<endl;
		
		file.close();
	}

	void compute_minSumProds(pair<vector<int>, vector<int>>& input_vectors, const unsigned& k, pair<int, size_t>& result)
	{
		//used for priority queue sorting descending, so the max diff between default product and changed one will be top
		std::function<bool(const pair<int, size_t>&, const pair<int, size_t>&)> cmp {[](const pair<int, size_t>& lhs, const pair<int, size_t>& rhs)
																							{return lhs.first<rhs.first;}
																						 };

		std::priority_queue<pair<int, size_t>, vector<pair<int, size_t>>, decltype(cmp)> pqueue(cmp);
		
		int sum{0}, default_product, changed_product;
		
		for(vector<int>::size_type idx{0}, dim = input_vectors.first.size(); idx<dim; ++idx)
		{
			default_product = input_vectors.first[idx]*input_vectors.second[idx];
			
			//Step 1: compute normal sum of products
			sum += default_product;
			
			//Step 2: compute changes
			if( (input_vectors.first[idx] <0 && input_vectors.second[idx] >0) || (input_vectors.first[idx] >=0 && input_vectors.second[idx] >=0) )
			{
				changed_product = (input_vectors.first[idx] -2*k)*input_vectors.second[idx];
			}
			if( (input_vectors.first[idx]>=0 && input_vectors.second[idx]<=0) || (input_vectors.first[idx]<0 && input_vectors.second[idx]<0) )
			{
				changed_product = (input_vectors.first[idx] +2*k)*input_vectors.second[idx];
			}
			
			//Step 3: in order to lower the sum, a prod needs to be lowered. To find which one find the max diff between the default product and the changed product
			pqueue.push(make_pair(abs(default_product-changed_product), idx));
		}
		//Step 4: the results is the normal sum minus max diff which is pqueue.top().first
		result = make_pair(sum-pqueue.top().first, pqueue.top().second);
	}
	
	void print_result(const pair<int, size_t>& result)
	{
		cout<<"Min sum: "<<result.first<<" change made on index: "<<result.second<<endl;
	}
}

void minSum_prodsElementsTwoArrays()
{
	std::pair<std::vector<int>, std::vector<int>> input_vectors;
	unsigned k;
	std::pair<int, size_t> result;
	
	minSum_prodsElements::read_input_vectors(input_vectors, k);
	minSum_prodsElements::compute_minSumProds(input_vectors, k, result);
	minSum_prodsElements::print_result(result);
	
}
