#include "standard_greedy_algorithms.hpp"

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
	std::cout<<std::endl<<"--------Activity selection. Tip: sort in descending order by end time. Then next chosen job has its start time greater than the last selected job end time--------"<<std::endl;
	//activity_selection();
	std::cout<<std::endl<<"--------Egyptian fraction. Tip: reverse fraction (so it becomes supraunitary) and ceil it (take next integer). Reverse the ceiling so 1/ceiling is obtained--------"<<std::endl;
	//egyptian_fraction();
	std::cout<<std::endl<<"--------Job sequencing. Tip: sort in descending order by profit. Then use an array of time_slots and consider deadline value as vector index to check for free slots--------"<<std::endl;
	//job_sequencing();
	std::cout<<std::endl<<"--------Job sequencing with loss minimization. Tip: sort in descending order by Loss/Time fraction--------"<<std::endl;	
	//job_sequencing_loss_minimization();
	std::cout<<std::endl<<"--------Huffman encoding--------"<<std::endl;
	huffman_encoding();
	std::cout<<std::endl<<"--------Huffman encoding for sorted input. Same data as above is used, so same output is expected--------"<<std::endl;
	huffman_encoding_sorted_input();
}
