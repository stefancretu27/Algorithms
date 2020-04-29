#include "standard_greedy_algorithms.hpp"

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
		for(vector<tuple<char, unsigned, unsigned>>::const_iterator it=jobs.begin(), end=jobs.end(); it!=end, idx < day_of_execution.size(); ++it, ++idx)
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
