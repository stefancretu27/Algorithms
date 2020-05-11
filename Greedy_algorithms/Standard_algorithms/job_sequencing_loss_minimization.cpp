#include "standard_greedy_algorithms.hpp"

/*
 * Problem description: Given a set of N jobs, each one being executed in a single unit of time (a day, let's say). Also, each job has associated 2 attributes:
 * 							1. time (deadline) = maximum number of days that can pass till it is executed
 * 							2. loss = if the deadline value is exceeded, a penalty is incured
 * 						It is aimed to find the jobs that can be executed in such a way that ensures the lowest loss.
 * 
 * Approach: It is observed that if the job sequencing approach is followed and the job array is sorted by loss, in descending order, there cannot be selected the maximum possible jobs.
 * 			 Thus, unlike previous job selection algorithm which takes into account the job's attributes sequentially (firstly, sorting by profit, then bookkeping deadlines in time_slots array), here both attributes must
 * be considered simultaneously. 
 * 			 Supposing all deadlines are equal, if jobs array is ordered by loss in descending order, the result with least loss is obtained, in this scenario. 
 * 			 However, if all loss values are equal, if jobs array is ordered by time in ascending order, this makes sure most jobs are executed in due time, leading to least loss result. Also, this is equivalent to 
 * sorting by 1/time descending.
 * 			 To consider both attributes at the same time, just order the jobs array in descending order by ratio loss/time
 * 
 * 			 So:
 * 				Step 1: sort the jobs by the ratio loss/time, in descending order
 * 				Step 2: define compare function for 2 fractions inputs (job1.loss* job2.time > job2.loss *job1.time)
 * 				Step 3: (optional) if after sorting there are 2 jobs whose fractions are equal and are executed fater their deadline, check if they can be swapped so one of it can be executed in due time.
 * 						As a job can be executed in a single unit of time, the deadline-index correlation is done. If the deadline is less than the index, it means that job's deadline passed and it's loss is incurred.
 * 						Thus, if a job's deadline is less than its index in the sorted vector (+1 as it is 0 based), then search in the remaining jobs for another one using similar condition. 
 * 						Once found, check if the second job's deadline is greater than or equal first's one index. If so, swap them.
 * 							
 */ 

namespace loss_minimization
{
	using namespace std;

	void read_jobs_by_line(vector<tuple<char, unsigned, unsigned>>& jobs)
	{
		ifstream file;
		file.open("jobs_sequencing_loss_minimization.txt", ios::in);
		
		string line;
		char id;
		unsigned loss, deadline;
		while(getline(file, line))
		{
			//treat each line like a stream of characters, instead of string object
			istringstream iss(line);
			//parse the stream of characters and read it in appropriate data types
			iss>>id>>loss>>deadline;
			//push the read data into the used data structure
			jobs.push_back(make_tuple(id, loss, deadline));
		}
		
		file.close();
	}

	void process_jobs(vector<tuple<char, unsigned, unsigned>>& jobs)
	{
		//Step 1: sort input vector in descending order by loss/time ratio. The need to sort by ratio comes from the fact that both attributes need to be taken into account simultaneously.
		//firstly, define lambda compare function to be used by sort. It compares 2 fractions as job1.loss/job1.deadline with job2.loss/job2.deadline.
		auto compare_fractions_greater {[](tuple<char, unsigned, unsigned>& job1, tuple<char, unsigned, unsigned> &job2) 
							{ 	
								return get<1>(job1)*get<2>(job2) > get<1>(job2)*get<2>(job1);
							} 
						  };
		sort(jobs.begin(), jobs.end(), compare_fractions_greater);
		

		//even though the below sequence has O(n^2) complexity, it also helps in reducing the loss. It aims at finding 2 jobs executed after the deadline
		for(unsigned idx = 0; idx < jobs.size()-1; ++idx)
		{
			//firstly, find a job executed after deadline. That is it's position in jobs array is greater than its deadline value
			if(get<2>(jobs[idx]) < idx+1)
			{	
				//once found, check if there is another one
				for(unsigned idy=idx+1; idy<jobs.size(); ++idy)
				{
					//if there is another one, also check if its deadline is >= than its position in jobs vector <=> can be executed no later than its deadline
					if(get<2>(jobs[idy]) < idy+1 && get<2>(jobs[idy]) >= idx+1)
					{
						tuple<char, unsigned, unsigned> swap = jobs[idx];
						jobs[idx] = jobs[idy];
						jobs[idy] = swap;
					}
				}
			}
		}
	}

	void print_jobs_vector(const vector<tuple<char, unsigned, unsigned>>& jobs)
	{
		cout<<" job id "<<" penalty "<<" deadline "<<" day of job execution"<<endl;
		for(vector<tuple<char, unsigned, unsigned>>::const_iterator it=jobs.cbegin(), end=jobs.cend(); it!=end; ++it)
		{
			cout<<"   "<<get<0>(*it)<<"        "<<get<1>(*it)<<"        "<<get<2>(*it)<<"        "<<it-jobs.begin()+1<<endl;
		}
	}
}

void job_sequencing_loss_minimization()
{
	std::vector<std::tuple<char, unsigned, unsigned>> jobs;
	
	loss_minimization::read_jobs_by_line(jobs);

	loss_minimization::process_jobs(jobs);
	
	loss_minimization::print_jobs_vector(jobs);
}
