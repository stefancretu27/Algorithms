#include "array_greedy_algorithms.hpp"

/*
 * Step-by-step solution: Greedy algorithms build the solution step-by step, with a decision being made at each step, in accordance to problem's domain, as it is done in optimization problems. 
 * Most immediate benefit choice: The choice made at each step is the one which offers the most immediate benefit in order to get close to the result.
 * Local optimization: As the solution is constructed piece by piece, the best choice made at each step represents a local optimization, but not necessarily a global optimization, with respect to problem's domain.
 * 					   Eg: Obtain 15 with least number of coins, by having coins {10,7,1}. The global optimum solution is 7+7+1 (3 coins), but it starts with 10 (most immediate benefit at step 1))=>10+1+1+1+1+1 (6 coins)
 * Generally, more efficient than dynamic programming techniques.
 * Sometimes, used to get an approximate solution for optimization problems as they yield an approximately optimal solution. 
 */ 

int main()
{
	std::cout<<std::endl<<"--------Min product subset. Tip: do not generate all possible subsets and then compute products. Instead, think of how input values might look like: all negatives, all zeroes etc--------"<<std::endl;
	min_product_subset();
	std::cout<<std::endl<<"--------Max product subset. Tip: Think of how input values might look like: all negatives, all zeroes, all positives, a mix of any from the previous etc--------"<<std::endl;
	max_product_subset();
	std::cout<<std::endl<<"--------Max sum after k negations. Tip: negate first k minimum elements => sort in ascending order/use priority queue etc--------"<<std::endl;
	max_sum_k_negations();
	std::cout<<std::endl<<"--------Max sum arr[index]*index. Tip: as the array's index increases in value, it should be multilied with the greater values in array => sort array in ascending order --------"<<std::endl;
	max_sum_elementMultipliedWithIndex();
	std::cout<<std::endl<<"--------Max sum of increasing order elements from M arrays. Tip: start with last array. If started with max value from 1st array, very possible not to reach the last vector --------"<<std::endl;
	maxSum_increasingOrderElementsFromNArrays();
	std::cout<<std::endl<<"--------Max sum of absolute differences of consecutive elements in circular array. Tip:Max differences are obtained if min and max elements are interleaved (a0 an a1 an-1 etc) --------"<<std::endl;
	maxSum_absoluteDifferencesOfConsecutiveElements();
	std::cout<<std::endl<<"--------Max difference of sums of k and N-k array partitions. Tip: If k <= size()/2, then choose the lowest k elements while the N-k are the greater --------"<<std::endl;
	maxDiff_sumsOfTwoArrayPartitions();
	std::cout<<std::endl<<"--------Max height pyramid. Tip: Start building top down using the lowest elements first => sort input ascending --------"<<std::endl;
	maxHeightPyramid();
	std::cout<<std::endl<<"--------Min sum of prods of 2 elements from 2 arrays. Tip: Computed default sum and for each default product compute the altered version. Then, substract by max abs difference--------"<<std::endl;
	minSum_prodsElementsTwoArrays();
	std::cout<<std::endl<<"--------Min sum of min values from pairs. Tip: Each pair should contain a min value and a max value. Thus, sort ascending and add first size/2 elements--------"<<std::endl;
	minSumFromMinValueOfPairs();
}
