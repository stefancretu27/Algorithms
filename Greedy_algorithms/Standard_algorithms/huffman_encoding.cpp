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

namespace huffman_encode
{
	using namespace std;
	
	typedef struct MinHeapNode
	{
		char character;
		unsigned frequency;
		shared_ptr<MinHeapNode> left, right;
		
		MinHeapNode(const char& c, const unsigned& u)
		{
			character = c;
			frequency = u;
			left = right = nullptr;
		};
		
	}MinHeapNode;

	void read_input_by_line(std::vector<std::pair<char, unsigned>>& input)
	{
		ifstream file;
		file.open("huffman_encoding.txt", ios::in);
		
		string line;
		char character;
		unsigned frequency;
		
		while(getline(file, line))
		{
			//treat each line like a stream of characters, instead of string object
			istringstream iss(line);
			//parse the stream of characters and read it in appropriate data types, using stringstream >> overloaded operator
			iss>>character>>frequency;
			//add data in internally used data structures
			input.push_back(std::make_pair(character, frequency));
		}
		
		file.close();
	}
	
	void printTreePreorder(const shared_ptr<MinHeapNode>& root)
	{
		if(root == nullptr)
			return;
			
		cout<<"   "<<root->character<<"        "<<root->frequency<<endl;
		printTreePreorder(root->left);
		printTreePreorder(root->right);
	}
	
	void generateCodesPreorder(const shared_ptr<MinHeapNode>& root, const string& bits, vector<pair<char, string>>& result)
	{
		if(root == nullptr)
			return;
		
		if(root->character != ' ')
		{	
			//cout<<"inserted character: "<<root->character<<"  Huffman encoding: "<<bits<<endl;
			result.push_back(make_pair(root->character, bits));
		}
		generateCodesPreorder(root->left, bits + "0", result);
		generateCodesPreorder(root->right, bits + "1", result);
	}

	void process_input(std::vector<std::pair<char, unsigned>>& input, vector<pair<char, string>>& result)
	{
		//Step 1: organize input data in a priority queue that sorts data in ascending order, by frequency
		//if the condition evaluates to true, the items are interchanged
		auto compare_ascending { [](const shared_ptr<MinHeapNode>& item1, const shared_ptr<MinHeapNode>& item2) 
							{ 	
								return item1->frequency > item2->frequency;
							} 
						  };
						  
		std::priority_queue<shared_ptr<MinHeapNode>, std::vector<shared_ptr<MinHeapNode>>, decltype(compare_ascending)> minHeap(compare_ascending);
		
		for(size_t idx = 0, dim = input.size(); idx < dim; ++idx)
		{
			//create the nodes dynamically in order to store the nodes in heap memory segment for persistency reasons
			minHeap.push(make_shared<MinHeapNode>(get<0>(input[idx]), get<1>(input[idx])));
		}
		
		/*
		 * Step 2: build the Huffman tree
		 * 		 - extract first 2 nodes and create a new node whose frequency is the sum of the frequencies of the extracted nodes. 
		 * 		 - the extracted nodes are added as children to the newly created node. The new node is added to minHeap.
		 * 		 - the process is repeated as long as minHeap has at lea 2 elements.
		 * 
		 * As the nodes are removed from minHeap, they should persist in memory as they are used in tree traversal afterwards
		 * Hence, the necessity of storing pointers to node in minHeap and to dynamically allocate them in heap segment.
		 */ 
		
		shared_ptr<MinHeapNode> firstNode, secondNode, newNode;
		
		while(minHeap.size() > 1)
		{
			//extract the first node by storing its data into an auxiliary created node and then remove it
			firstNode = minHeap.top();
			//remove first node
			minHeap.pop();
			
			//extract the second node by storing its data into an auxiliary created node and then remove it
			secondNode = minHeap.top();
			//remove second node
			minHeap.pop();
			
			//create new node from the new first node (that is the secondly extracted node) and the 
			newNode = make_shared<MinHeapNode>(' ', firstNode->frequency + secondNode->frequency);
			newNode->left = firstNode;
			newNode->right = secondNode;
			
			//add the newly created node to minHeap
			//when there are only two nodes left, this new node is the root node of the tree and the loop ends. Also, it will be the only node in minHeap
			minHeap.push(newNode);
		}
		
		//Step 3: generate codes by DFS-traversing the Huffman tree processed baove
		generateCodesPreorder(minHeap.top(), "", result);
	}
}

void huffman_encoding()
{
	std::vector<std::pair<char, unsigned>> input;
	
	huffman_encode::read_input_by_line(input);

	std::vector<std::pair<char, std::string>> result;
	huffman_encode::process_input(input, result);
	
	std::cout<<"inserted character    	Huffman encoding"<<std::endl;
	for(auto it = result.cbegin(), end = result.cend(); it!=end; ++it)
	{
		std::cout<<"	"<<it->first<<"			"<<it->second<<std::endl;
	}
}
