#include "standard_greedy_algorithms.hpp"

/*
 * Problem description: Given a set of N jobs, each one being executed in a single unit of time (a day, let's say). Also, each job has associated 2 attributes:
 * 							1. deadline = maximum number of days that can pass till it is executed
 * 							2. profit = reward gained if the job is executed till the deadline. If a job has deadline 4 and is executed on the 4th day, the profit is still awarded.
 * 						It is aimed to find the jobs that can be executed in such a way that ensures maximum profit.
 * 
 * Approach: As a Greedy algorithm, it aims at maximizing the profit. Thus, first of all, the job that offers the biggest profit is selected. For this, the jobs array is sorted in descending order by profit.
 * 			 As the array is sorted, iterate over it to check which of the remaining jobs can be chosen. In order to determine is a job can be selected, an additional array of boolean values is used.
 * 			 This array, called time_slots, bookkeeps the time slots occuppied by the selected jobs as follows and it has the following characteristics:
 * 					 - the time_slots array has the same length as the problem's domain, as the maximum possible selectable jobs is equal to the number of the jobs in the input array
 * 					 - the array is initialized to false, telling there is no job selected 
 * 					 - once the jobs array is sorted and the first job is selected (as it gives the maximum profit), the first time_slot is set to true
 *     				 - while it is iterated over the jobs array, for each job it is verified if it would have a free spot in time_array. For this, it is iterated over time_slots array. 
 *                   - Here, a correlation between the index and the deadline is made, as any given job can be executed in a single unit of time, each index can be perceived as such a unit of time. 
 *                   - this way, in the job seelction process is taken into account the deadline value, as the profit was already considered when sorting
 * 					 - Therefore, a job's deadline value indicates the maximum index in the time_slots array the it should be search for a free spot. If the deadline value is greater than the problem's size, then the
 * latter is considered for indexation. 
 * 					 - That said, for every encountered job, the iteration over the time_slots array should start with index = min(job.deadline, problem_size) till index 1 (including). 
 *                   - this way it is ensured that if there are more jobs with the same deadline value, the ones with higher profits have higher chances to find a free slot in time_slots array, following the greedy approach.
 * 
 * 			 So:
 * 				Step 1: sort the job by their profit values, in descending order
 * 				Step 2: choose first job in the list by appending it to the results array, as it has the highest profit and mark the first position in time_slots array as true
 * 				Step 3: iterate over the remaining activities in list. At each iteration, also iterate over the time_slots array in descending order, strating with index = min(job.deadline, jobs_array.size). Substract 1 
 * for 0 based indexation compliance. Then, check if the value at any given index in time_slots array is false. If so, mark it as true and append the current job to results array.
 */ 

namespace job_seq
{
	using namespace std;

	void read_jobs_by_line(vector<tuple<char, unsigned, unsigned>>& jobs)
	{
		ifstream file;
		file.open("jobs_sequencing.txt", ios::in);
		
		string line;
		char id;
		unsigned deadline, profit;
		while(getline(file, line))
		{
			//treat each line like a stream of characters, instead of string object
			istringstream iss(line);
			//parse the stream of characters and read it in appropriate data types
			iss>>id>>deadline>>profit;
			//push the read data into the used data structure
			jobs.push_back(make_tuple(id, deadline, profit));
		}
		
		file.close();
	}

	void process_jobs(vector<tuple<char, unsigned, unsigned>>& jobs, vector<tuple<char, unsigned, unsigned>>& result, vector<bool>& time_slots, vector<unsigned>& day_of_execution)
	{
		//Step 1: sort input vector in descending order by profit
		//firstly, define lambda compare function to be used by sort
		auto compare_profit_greater {[](tuple<char, unsigned, unsigned>& t1, tuple<char, unsigned, unsigned> &t2) 
							{ 
								return get<2>(t1) > get<2>(t2);
							} 
						  };
		sort(jobs.begin(), jobs.end(), compare_profit_greater);
		
		//Step 2: first element in sorted input vector is the first job in sequence, so push it to result and mark the first position in time slots as taken, regardless the job's deadline value
		result.push_back(jobs.front());
		time_slots.front() = true;
		day_of_execution.push_back(1);			//store the id of day/unit time of the job's execution

		size_t max_index;
		for(vector<tuple<char, unsigned, unsigned>>::iterator it = jobs.begin()+1, end = jobs.end(); it!=end; ++it)
		{
			//the current job's maximum possible time slot can be found at the index equal to minimum of its deadline and jobs vector size
			//it is aimed to place the job on its maximum possible index in free slots array in order to make sure there is always free slots for jobs that offer most profit, as the jobs array is sorted descending by profit 
			//substract 1 for 0 based indexing
			max_index = min(get<1>(*it), static_cast<unsigned>(jobs.size())) - 1; 
			for(size_t idx=max_index; idx>0; --idx)
			{
				//if the job has a free time slot
				if(time_slots[idx]==false)
				{
					result.push_back(*it);						//added it to result
					time_slots[idx]=true;						//mark its time slot as taken
					day_of_execution.push_back(idx+1); 			//store the id of day/unit time of the job's execution
					break;										//do not search for further free slots, but proceed with the next jobs
				}
			}
		}
	}
	
	void print_jobs_vector(const vector<tuple<char, unsigned, unsigned>>& jobs, vector<unsigned>& day_of_execution)
	{
		cout<<" job id "<<" deadline "<<" profit "<<" day of execution"<<endl;
		unsigned idx{0};
		for(vector<tuple<char, unsigned, unsigned>>::const_iterator it=jobs.cbegin(), end=jobs.cend(); it!=end, idx < day_of_execution.size(); ++it, ++idx)
		{
			cout<<"   "<<get<0>(*it)<<"        "<<get<1>(*it)<<"        "<<get<2>(*it)<<"       "<<day_of_execution[idx]<<endl;
		}
	}

}


void job_sequencing()
{
	std::vector<std::tuple<char, unsigned, unsigned>> jobs, result;
	std::vector<unsigned> day_of_execution;
	
	job_seq::read_jobs_by_line(jobs);

	std::vector<bool> time_slots(jobs.size());
	std::fill(time_slots.begin(), time_slots.end(), false);
	
	job_seq::process_jobs(jobs, result, time_slots, day_of_execution);
	
	job_seq::print_jobs_vector(result, day_of_execution);
}
