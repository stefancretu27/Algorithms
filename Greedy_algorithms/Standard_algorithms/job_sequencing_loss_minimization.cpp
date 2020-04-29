#include "standard_greedy_algorithms.hpp"

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
		//Step 1: sort input vector in descending order by loss/time ration
		//firstly, define lambda compare function to be used by sort. It compares 2 fractions as job1.loss/job1.deadline with job2.loss/job2.deadline.
		auto compare_fractions_greater {[](tuple<char, unsigned, unsigned>& job1, tuple<char, unsigned, unsigned> &job2) 
							{ 
								return get<1>(job1)*get<2>(job2) > get<1>(job2)*get<2>(job1);
							} 
						  };
		sort(jobs.begin(), jobs.end(), compare_fractions_greater);
		
	}

	void print_jobs_vector(const vector<tuple<char, unsigned, unsigned>>& jobs)
	{
		cout<<" job id "<<" penalty "<<" deadline "<<" day of job execution"<<endl;
		for(vector<tuple<char, unsigned, unsigned>>::const_iterator it=jobs.begin(), end=jobs.end(); it!=end; ++it)
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
