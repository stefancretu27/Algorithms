#include "array_greedy_algorithms.hpp"

/* Partition into two subarrays of lengths k and (N – k) such that the difference of sums is maximum
 * 
 * Problem description: Given an array of N integers and an integer k such as 0<k<N it is aimed to partition the array into 2 subarrays of sizes k and N-k such as the difference between the sums of elements in each 
 * 						partition is maximum.
 * 
 * Approach: Since the difference has to be maximum, the small values should be isolated from bigger values. Thus, one partition should contain the small values and the other the big values. In order to further 
 * 			 maximize the result, the small values should be placed on the partition with lower length. Thus, if k < array.size()/2, sort ascending ad compute sum of first k elements then sum of the rest N-k. Else,
 * 			 sort descending. 
 */ 

namespace max_diff_sums_partitions
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

	void compute_diff_partitionsSums(vector<pair<vector<int>, unsigned>>& input_vectors, vector<tuple<int,int,int>>& sumsAndDiff)
	{
		//Perform algorithm for multiple input vectors
		for(auto& pairObj : input_vectors)
		{
			//get the value of k and retrieve vector size
			unsigned k = pairObj.second;
			vector<int>::size_type dim = pairObj.first.size();
			
			//Step 1: sort input vector in ascending order. Use lambda for the sake of syntax. If the conditions is true, std::sort does not interchange elements
			std::function<bool(const int&, const int&)> cmp_less {[](const int& lhs, const int& rhs)
																{return lhs<rhs;}
															};
															
			std::function<bool(const int&, const int&)> cmp_greater{[](const int& lhs, const int& rhs){return lhs>rhs;}};
			
			//Step 2: compute the sums
			if(k <= dim/2)
			{
				cout<<"array size: "<<dim<<" k: "<<k<<" sorting ascendig"<<endl;
				sort(pairObj.first.begin(), pairObj.first.end(), cmp_less);
			}
			else
			{
				cout<<"array size: "<<dim<<" k: "<<k<<" sorting descendig"<<endl;
				sort(pairObj.first.begin(), pairObj.first.end(), cmp_greater);
			}	
			
			int sumK{0}, sumNMinusK{0};
			for(vector<int>::size_type idx{0}; idx<k; ++idx)
			{
				sumK += pairObj.first[idx];
			}
			for(vector<int>::size_type idx{k}; idx<dim; ++idx)
			{
				sumNMinusK += pairObj.first[idx];
			}
			
			sumsAndDiff.push_back(make_tuple(sumK,sumNMinusK, abs(sumK-sumNMinusK)));
		}
	}
	
	void print_result(const std::vector<std::tuple<int,int,int>>& sumsAndDiff)
	{
		//cout<<" job id "<<" deadline "<<" profit "<<" day of execution"<<endl;
		for(auto it=sumsAndDiff.cbegin(), end=sumsAndDiff.cend(); it!=end; ++it)
		{
			cout<<"Array: "<< it-sumsAndDiff.cbegin()<<" Sum of first k elements "<<std::get<0>(*it)<<" Sum of N-k elements: "<<std::get<1>(*it)<<" Difference: "<<std::get<2>(*it)<<endl;
		}
	}
}

void maxDiff_sumsOfTwoArrayPartitions()
{
	std::vector<std::pair<std::vector<int>, unsigned>> input_vectors;
	std::vector<std::tuple<int,int,int>> sumsAndDiff;
	
	max_diff_sums_partitions::read_input_vectors(input_vectors);
	max_diff_sums_partitions::compute_diff_partitionsSums(input_vectors, sumsAndDiff);
	max_diff_sums_partitions::print_result(sumsAndDiff);
	
}
