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
		std::vector<s_job> result;
		std::vector<s_job>::size_type out_idx{0};
		
		//step 1: sort vector
		std::sort(input.begin(), input.end(), compare_jobs);
		//step 2: choose first element
		result.push_back(input[out_idx]);
		
		for(std::vector<s_job>::size_type idx{1}, dim=input.size(); idx<dim; idx++)
		{
			if(input[idx].start >= result[out_idx].end)
			{
				result.push_back(input[idx]);
				++out_idx;
			}
		}
		
		std::cout<<"simplistic implementation result: "<<std::endl;
		print_jobs(result);
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
		
		//use own defined lambda greater as compare function for std::sort. By default, it uses < to srt elements ascending. 
		//If the condition evaluates to false, the items are interchanged. In other words, the condition shows the order of elements we want to have in the array after sorting
		auto job_pair_less_compare{[](pair<unsigned,unsigned> x, pair<unsigned,unsigned> y)
									{
										return x.second<=y.second;
									}
								  };
		
		//just playing around with syntax						  
		std::function<bool(pair<unsigned,unsigned>, pair<unsigned, unsigned>)> job_pair_greater{ [](pair<unsigned,unsigned> p1, pair<unsigned, unsigned> p2)
																									{
																										return p1.second > p2.second;
																									}			
																							};											
		//step 1: sort jobs vector using std::sort which has O(N log N) complexity
		sort(jobs.begin(), jobs.end(), job_pair_less_compare);
		
		std::cout<<"inserted jobs sorted by end time in ascending order : "<<endl;
		print_jobs(jobs);
		
		//step 2: choose 1st element in sorted list of jobs
		result.push_back(jobs.front());
		
		//step 3: iterate over the rest of jobs and chose, at each step, the first in the list whose start time >= end time of previous
		for(vector<pair<unsigned,unsigned>>::iterator it = jobs.begin(), end = jobs.end(); it!=end; ++it)
		{
			if(it->first >= result.back().second)
			{
				result.push_back(*it);
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
		
		//as priority_queue uses less to sort elements in descending order, provide own defined lambda to sort in ascending order
		//if the condition evaluates to true, the items are interchanged
		auto job_pair_greater_compare{[](pair<unsigned,unsigned> x, pair<unsigned,unsigned> y){return x.second>y.second;}};
		
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

void line_file_parser(std::vector<simplistic_solution::s_job>& jobs)
{
	//file object used for reading
	std::ifstream file;
	//open file for reading
	file.open("activities.txt", std::ios::in);
	
	simplistic_solution::s_job job_inst; 
	//read each line as a sequence of characters and store it in a string object
	std::string line;
	while(std::getline(file, line))
	{
		//stream of characters which can be treated like a string object
		std::istringstream iss(line);
		iss>>job_inst.start>>job_inst.end;
		jobs.push_back(job_inst);
	}
	
	//close file
	file.close();
}

void line_file_parser(std::vector<std::pair<unsigned,unsigned>>& jobs)
{
	//file object used for reading
	std::ifstream file;
	//open file for reading
	file.open("activities.txt", std::ios::in);
	
	unsigned start, end;
	//read each line as a sequence of characters and store it in a string object
	std::string line;
	while(std::getline(file, line))
	{
		//stream of characters which can be treated like a string object
		std::istringstream iss(line);
		iss>>start>>end;
		jobs.push_back(std::make_pair(start, end));
	}
	
	//close file
	file.close();
}


void activity_selection()
{
	
	std::cout<<"simplistic solution"<<std::endl;
	std::vector<simplistic_solution::s_job> s_jobs;
	line_file_parser(s_jobs);
	simplistic_solution::simplistic_activity_selection(s_jobs);
	
	std::vector<std::pair<unsigned,unsigned>> jobs; 
	line_file_parser(jobs);
	
	std::cout<<std::endl<<"cpp solution"<<std::endl;
	cpp_solution::cpp_activity_selection(jobs);
	std::cout<<std::endl<<"stl solution"<<std::endl;
	stl_solution::stl_activity_selection(jobs);
	
	
}
