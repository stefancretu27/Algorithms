#include "standard_greedy_algorithms.hpp"

/*
 * Given a set of N activities with their afferent starting times and end times, the aim is to choose the maximum jobs a person can do, given one job can be executed at a time.
 * Approach: The chosen activities must not overlap. Therefore, the next chosen's activity starting time should be >= that the previous job end time.
 * 			 Also, as there should be chosen the maximum number of jobs, the one that offers the most immediate benefit is the one that finishes first. 
 * 			 So:
 * 				Step 1: sort the activities by their finish times, in ascending order
 * 				Step 2: choose first activity in the list, as it has the lowest finish time (finishes first)
 * 				Step 3: iterate over the remaining activities in list. At each iteration check if the current job's start time is >= than previous end time. If so, choose it and proceed further.
 */ 

namespace simplistic_solution
{
	typedef struct job
	{
		unsigned start, end;
		
		struct job& operator=(const struct job& j)
		{
			start = j.start;
			end = j.end;
			return *this;
		}
		
	}s_job;
	
	bool compare_jobs(const s_job& j1, const s_job& j2)
	{
		return (j1.end<=j2.end);
	}
	
	void print_jobs(const std::vector<s_job>& input)
	{
		for(std::vector<s_job>::size_type idx{0}, dim=input.size(); idx<dim; idx++)
			std::cout<<"start time: "<<input[idx].start<<" end time: "<<input[idx].end<<std::endl;
	}
	
	void simplistic_activity_selection(std::vector<s_job> &input)
	{
		std::vector<s_job> output;
		std::vector<s_job>::size_type out_idx{0};
		
		//step 1: sort vector
		std::sort(input.begin(), input.end(), compare_jobs);
		//step 2: choose first element
		output.push_back(input[out_idx]);
		
		for(std::vector<s_job>::size_type idx{1}, dim=input.size(); idx<dim; idx++)
		{
			if(input[idx].end >= output[out_idx].start)
			{
				output[++out_idx] = input[idx];
			}
		}
		
		std::cout<<"simplistic implementation result: "<<std::endl;
		print_jobs(output);
	}
}

namespace cpp_solution
{
	using namespace std; 
	
	void print_jobs(const vector<pair<unsigned,unsigned>>& result)
	{
		for(vector<pair<unsigned,unsigned>>::const_iterator it = result.cbegin(), end = result.cend(); it!=end; ++it)
		{
			cout<<"    start time: "<<it->first<<" end time: "<<it->second<<endl;
		}
	}
	
	//passing a ref to const vector would mean all iterators must be const. Also, it needs to be modified by std::sort
	void cpp_activity_selection(vector<pair<unsigned,unsigned>> &jobs)
	{
		vector<pair<unsigned,unsigned>> result;
		vector<pair<unsigned,unsigned>>::size_type result_idx{0};
		
		//use own defined lambda greater as compare function for std::sort. By default, it uses < to srt elements ascending
		auto job_pair_less_compare{[](pair<unsigned,unsigned> x, pair<unsigned,unsigned> y){return x.second<=y.second;}};
		
		//step 1: sort jobs vector using std::sort which has O(N log N) complexity
		sort(jobs.begin(), jobs.end(), job_pair_less_compare);
		
		std::cout<<"inserted jobs sorted by end time: "<<endl;
		print_jobs(jobs);
		
		//step 2: choose 1st element in sorted list of jobs
		result.push_back(jobs.front());
		
		//step 3: iterate over the rest of jobs and chose, at each step, the first in the list whose start time >= end time of previous
		for(vector<pair<unsigned,unsigned>>::iterator it = jobs.begin(), end = jobs.end(); it!=end; ++it)
		{
			if(it->first >= result[result_idx].second)
			{
				result.push_back(*it);
				++result_idx;
			}
		}
		
		cout<<"cpp_implementation result: "<<endl;
		print_jobs(result);
	}
}

namespace stl_solution
{
	//use priority queue as container adapter for jobs to sort jobs in ascending order
	using namespace std; 
	
	void print_jobs(const vector<pair<unsigned,unsigned>>& result)
	{
		for(vector<pair<unsigned,unsigned>>::const_iterator it = result.cbegin(), end = result.cend(); it!=end; ++it)
		{
			cout<<"    start time: "<<it->first<<" end time: "<<it->second<<endl;
		}
	}
	
	void stl_activity_selection(vector<pair<unsigned,unsigned>> &jobs)
	{
		vector<pair<unsigned,unsigned>> result;
		
		//as priority_queue uses less to sort elemnts in descending order, provide own defined lambda to sort in ascending order
		auto job_pair_greater_compare{[](pair<unsigned,unsigned> x, pair<unsigned,unsigned> y){return x.second>=y.second;}};
		
		//template args: type of data in container, container, compare function with data type. As lambda does not bear a data type, use decltype to infer it
		priority_queue< pair<unsigned, unsigned>, vector<pair<unsigned, unsigned>>, decltype(job_pair_greater_compare)> prio_jobs(job_pair_greater_compare);
		
		//step 1: sorting job list
		//instead of using sort with NLogN, use more memory and N traversial
		for(vector<pair<unsigned,unsigned>>::iterator it{jobs.begin()}, end{jobs.end()}; it!=end; ++it)
		{
			prio_jobs.push(*it);
		}
		
		//step 2: take 1st element in sorted queue
		result.push_back(prio_jobs.top());
		//remove the element
		prio_jobs.pop();
		
		//step 3: iterate over remining jobs
		while(!prio_jobs.empty())
		{
			//always take the first pair in prio queue
			auto first_pair = prio_jobs.top();
			prio_jobs.pop();
			if(first_pair.first >= result.back().second)
			{
				result.push_back(first_pair);
			}
		}
		
		cout<<"stl_implementation result: "<<endl;
		print_jobs(result);
	}
}

void activity_selection()
{
	std::vector<std::pair<unsigned,unsigned>> jobs{ {5, 8}, {9, 13}, {0, 5}, {1, 2}, {4, 5}, {5, 9}};
	
	cpp_solution::cpp_activity_selection(jobs);
	stl_solution::stl_activity_selection(jobs);
}
