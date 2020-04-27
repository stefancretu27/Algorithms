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
	//activity_selection();
	egyptian_fraction();	
}
