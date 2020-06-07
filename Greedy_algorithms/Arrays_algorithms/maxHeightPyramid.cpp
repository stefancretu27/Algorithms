#include "array_greedy_algorithms.hpp"

/* Find max height of the pyramid that can be formed from the elements of the input array
 * 
 * Problem description: Given an array of N integers, with each value representing a weight, it is aimed to build a pyramid from this elements, in a top-down manner, based on the following two conditions:
 *							- the number of lements at level i+1 is greater than the number of elements at level i (so to get the pyramid like structure)
 *							- the total weight at level i+1 is greater than the total weight at level i 
 * 
 * Approach: Since the values represent weights and each new level has higher weight than the previous, it is intuitively true that the first step should entail sorting the input array in ascending order.
 * 			 Also, when building a level i, check if the remainig elements count is enough to form a new level i+1. If not, just add the remaining elements to the newly built level which is the base of the pyramid.
 */ 

namespace max_height_pyramid
{
	using namespace std;

	void read_input_vectors(vector<vector<unsigned >>& input_vectors)
	{
		ifstream file;
		file.open("pyramids.txt", ios::in);
		
		string line;
		unsigned value;
		vector<unsigned> temp;
		
		while(getline(file, line))
		{
			//erase previously read vector
			temp.clear();
			
			//treat each line like a stream of values, instead of string object. 
			istringstream iss(line);

			cout<<"vector values: ";
			//parse the string into integers
			while(iss>>value)
			{
				cout<<value<<" ";
				//push the read data into the used data structure
				temp.push_back(value);
			}
			cout<<endl;
			input_vectors.push_back(temp);
		}
		
		file.close();
	}

	void compute_maxHeight(vector<vector<unsigned>>& input_vectors, vector<vector<list<unsigned>>>& pyramids)
	{
		//Perform algorithm for multiple input vectors
		for(auto& vec : input_vectors)
		{
			//Step 1: sort input vector in ascending order. Use lambda for the sake of syntax. If the conditions is true, std::sort does not interchange elements
			std::function<bool(const unsigned&, const unsigned&)> cmp_less {[](const unsigned& lhs, const unsigned& rhs)
																				{return lhs<rhs;}
																			};

			sort(vec.begin(), vec.end(), cmp_less);
			
			//Step 2: the top of the pyramid is the first element in the array
			list<unsigned> new_level;
			new_level.push_back(vec.front());
			
			//add the new level to the vector of lists, representing the pyramid
			vector<list<unsigned>> pyramid;
			pyramid.push_back(new_level);
			
			//keep track of the weight of previous level. The size is retrieved using pyramid.back().size() to get the # of elements of the last inserted level (list)
			unsigned prev_weight{vec.front()};
			//use counter for the current weight
			unsigned curr_weight{0};
			
			new_level.clear();
			for(vector<unsigned>::const_iterator it = vec.cbegin()+1, end = vec.cend(); it!=end; ++it)
			{
				//adjust the current weigh to a new value
				curr_weight += *it;
				//build the new level by adding the current indexed element
				new_level.push_back(*it);
				
				if(new_level.size() > pyramid.back().size() && curr_weight > prev_weight)
				{
					//before inserting the new level, check if the number of remaining elements is greater then the current's level size. If not, append the remaining elements to the current level
					if(new_level.size() >= static_cast<unsigned>(end-it-1))
					{
						for(auto curr_pos = it+1; curr_pos!=end; ++curr_pos)
						{
							new_level.push_back(*curr_pos);
						}
					}
					//insert new level
					pyramid.push_back(new_level);
					
					//clear the list for being reused in the next iterations
					new_level.clear();
					//reset the weight counter
					prev_weight = curr_weight;
					curr_weight = 0;
				}
			}
			
			pyramids.push_back(pyramid);
			pyramid.clear();
		}
	}
	
	void print_pyramid(const vector<vector<list<unsigned>>>& pyramids)
	{
		for(auto pyramid : pyramids)
		{
			cout<<"Pyramid height is: "<<pyramid.size()<<endl<<"Display pyramid by levels:"<<endl;
			for(auto level : pyramid)
			{
				for(list<unsigned>::const_iterator it = level.cbegin(), end = level.cend(); it!= end; ++it)
				{
					cout<<*it<<" ";
				}
				cout<<endl;
			}
		}
	}
}

void maxHeightPyramid()
{
	std::vector<std::vector<unsigned>> input_vectors;
	std::vector<std::vector<std::list<unsigned>>> pyramid;
	
	max_height_pyramid::read_input_vectors(input_vectors);
	max_height_pyramid::compute_maxHeight(input_vectors, pyramid);
	max_height_pyramid::print_pyramid(pyramid);
	
}
