#include "array_greedy_algorithms.hpp"

/* Partition into two subarrays of lengths k and (N – k) such that the difference between the sums of the elements from these subarrays is maximum
 * 
 * Problem description: Given an array of N integers and an integer k such as 0<k<N it is aimed to partition the array into 2 subarrays of sizes k and N-k such as the difference between the sums of elements in each 
 * 						partition is maximum.
 * 
 * Approach: Since the difference has to be maximum, the small values should be isolated from bigger values. Thus, one partition should contain the small values and the other the big values. In order to further 
 * 			 maximize the result, the small values should be placed on the partition with lower length. 
 * 			 Thus, approach would be to sort ascending or descending, as follows: if k <= array.size()/2, sort ascending ad compute sum of first k elements then sum of the rest N-k. Else, sort descending. 
 * 			 Another approach would be to sort ascending. Then, if k<=array.size()/2, first k elements are the lower valued ones, with the rest N-k being the higher valued, so compute sums of these 2 subarrays. However,
 * 			 if k > array/size()/2, first N-k values are the lower sized ones, with the rest k being the high valued ones. Basically, instead of sorting distinctly based on k's value , just partition the sorted array
 * 			 appropriately.
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

	void compute_diff_partitionsSums_approach1(vector<pair<vector<int>, unsigned>>& input_vectors, vector<tuple<int,int,int>>& sumsAndDiff)
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
			//Step 2: compute the sums
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
	
		void compute_diff_partitionsSums_approach2(vector<pair<vector<int>, unsigned>>& input_vectors, vector<tuple<int,int,int>>& sumsAndDiff)
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
			cout<<"array size: "<<dim<<" k: "<<k<<" sorting ascendig"<<endl;
			sort(pairObj.first.begin(), pairObj.first.end(), cmp_less);
			
			//Step 2: compute the sums
			int sumK{0}, sumNMinusK{0};
			if(k <= dim/2)
			{
				cout<<"k <= size()/2 => first k elements are the lower valued ones"<<endl;
				for(vector<int>::size_type idx{0}; idx<k; ++idx)
				{
					sumK += pairObj.first[idx];
				}
				for(vector<int>::size_type idx{k}; idx<dim; ++idx)
				{
					sumNMinusK += pairObj.first[idx];
				}
			}
			else
			{
				cout<<"k > size()/2 => first size()-k elements are the lower valued ones"<<endl;
				for(vector<int>::size_type idx{0}; idx<dim-k; ++idx)
				{
					sumK += pairObj.first[idx];
				}
				for(vector<int>::size_type idx{dim-k}; idx<dim; ++idx)
				{
					sumNMinusK += pairObj.first[idx];
				}
			}	
			
			sumsAndDiff.push_back(make_tuple(sumK,sumNMinusK, abs(sumK-sumNMinusK)));
		}
	}
	
	void print_result(const std::vector<std::tuple<int,int,int>>& sumsAndDiff)
	{
		//cout<<" job id "<<" deadline "<<" profit "<<" day of execution"<<endl;
		for(auto it=sumsAndDiff.cbegin(), end=sumsAndDiff.cend(); it!=end; ++it)
		{
			cout<<"Array: "<< it-sumsAndDiff.cbegin()<<" Sum of 1st subarray "<<std::get<0>(*it)<<" Sum of 2nd subarray: "<<std::get<1>(*it)<<" Difference: "<<std::get<2>(*it)<<endl;
		}
	}
}

void maxDiff_sumsOfTwoArrayPartitions()
{
	std::vector<std::pair<std::vector<int>, unsigned>> input_vectors;
	std::vector<std::tuple<int,int,int>> sumsAndDiff;
	
	max_diff_sums_partitions::read_input_vectors(input_vectors);
	max_diff_sums_partitions::compute_diff_partitionsSums_approach1(input_vectors, sumsAndDiff);
	max_diff_sums_partitions::print_result(sumsAndDiff);
	
	sumsAndDiff.clear();
	std::cout<<"Aproach 2, using one sorting and partition the sorted array based on k value with respec to array.size()/2"<<std::endl;
	max_diff_sums_partitions::compute_diff_partitionsSums_approach2(input_vectors, sumsAndDiff);
	max_diff_sums_partitions::print_result(sumsAndDiff);
}
