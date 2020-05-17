#include "standard_greedy_algorithms.hpp"

/*
 * Problem description: Given a set of characters alongside their frequencies of occurrence in some text, it is aimed at finding a non-ambiguous coding that maps each character to a unque sequence of bits.
 * 						The characters with lower occurrence rates are encoded to longer bit sequences, when compared to characters that have higher frequency rate.
 * 
 * Approach: Step 1 (read input): the characters and their frequency values are read from input and stored in a vector<pair>
 * 			  
 * 			 Step 2 (build Huffman tree): This requires to dynamically create nodes, that can be pushed and poped from a queue, without losing that information.
 *            	- since it is a Greedy algorithm, it aims at finding the less frequent characters first. Thus, the nodes should be sorted in ascending order by their frequency value. So, use priority_queue to store them.
 * 			  	- untill this queue contains one node, take the first two nodes and create a new node from them, whose frequency is the sum of the extracted nodes. The first extracted nodes becomes the left child of the
 * 	newly created nodes, whereas the second extracted node becomes the right child. Thus, nodes with lower frequencies can be found on the left side of the tree.
 * 				- when only one node is contained in the priority_queue, then the tree is completely built, as it is the sum of the previously extracted 2 nodes and it has these nodes already set as its children.
 *           
 * 			 Step 3 (assign codes): Once the binary tree is built, traverse it in preorder: check root if it has a character stored, then recursively do the same for left child, then for right child 
 * (root->left->right approach)
 * 				- maintain an auxiliary array. When traversing a left node, push 0 to this vector, and push 1 when traversing a right node. If the node contains a character, print the character and the values stored in
 * the vector. It shows the bit sequence encoding for that character
 */ 

namespace huffman_encode_sortedInput
{
	using namespace std;
	
	typedef struct TreeNode
	{
		char character;
		unsigned frequency;
		shared_ptr<TreeNode> left, right;
		
		TreeNode(const char& c, const unsigned& u)
		{
			character = c;
			frequency = u;
			left = right = nullptr;
		};
		
	}TreeNode;

	void read_input_by_line(std::vector<std::pair<char, unsigned>>& input)
	{
		ifstream file;
		file.open("huffman_encoding_sorted_input.txt", ios::in);
		
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
	
	void printTreePreorder(const shared_ptr<TreeNode>& root)
	{
		if(root == nullptr)
			return;
			
		cout<<"   "<<root->character<<"        "<<root->frequency<<endl;
		printTreePreorder(root->left);
		printTreePreorder(root->right);
	}
	
	void generateCodesPreorder(const shared_ptr<TreeNode>& root, const string& bits, vector<pair<char, string>>& result)
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
	
	shared_ptr<TreeNode> extractMinNode(queue<shared_ptr<TreeNode>>& queue1, queue<shared_ptr<TreeNode>>& queue2)
	{	
		shared_ptr<TreeNode> returnNode;
		
		if(queue1.empty())
		{
			if(queue2.empty())
				return nullptr;
			else
			{
				returnNode = queue2.front();
				queue2.pop();
				return returnNode;
			}
		}
		
		if(queue2.empty())
		{
			if(queue1.empty())
				return nullptr;
			else
			{
				returnNode = queue1.front();
				queue1.pop();
				return returnNode;
			}
		}
		
		if(queue1.front()->frequency < queue2.front()->frequency)
		{
			returnNode = queue1.front();
			queue1.pop();
			return returnNode;
		}
		else
		{
			returnNode = queue2.front();
			queue2.pop();
			return returnNode;
		}
		
	}

	void process_input(std::vector<std::pair<char, unsigned>>& input, vector<pair<char, string>>& result)
	{
		queue<shared_ptr<TreeNode>> queue1, queue2;
		
		/*
		 * Step 1: for each element in the input data, dynamically freate a TreeNode and add it to queue 1
		 */ 
		for(size_t idx = 0, dim = input.size(); idx < dim; ++idx)
		{
			//create the nodes dynamically in order to store the nodes in heap memory segment for persistency reasons
			queue1.push(make_shared<TreeNode>(input[idx].first, input[idx].second));
		}
		
		/*
		 * Step 2: build the Huffman tree
		 * 		 - extract first 2 nodes and create a new node whose frequency is the sum of the frequencies of the extracted nodes. 
		 * 		 - the extracted nodes are added as children to the newly created node. The new node is added to the queue 2.
		 * 		 - the process stops when queue 1 is empty and queue2 contains one node.
		 * 		 - the extracted nodes are min(queue1.front, queue2.front)
		 * 
		 * As the nodes are removed from minHeap, they should persist in memory as they are used in tree traversal afterwards
		 * Hence, the necessity of storing pointers to node in minHeap and to dynamically allocate them in heap segment.
		 */ 
		
		shared_ptr<TreeNode> firstNode, secondNode, newNode;
		
		while(queue1.size()>0)
		{
			//extract the first node by storing its data into an auxiliary created node and then remove it
			firstNode = extractMinNode(queue1, queue2);

			//extract the second node by storing its data into an auxiliary created node and then remove it
			secondNode = extractMinNode(queue1, queue2);
			
			if(firstNode==nullptr || secondNode==nullptr)
				break;

			//create new node from the new first node (that is the secondly extracted node) 
			newNode = make_shared<TreeNode>(' ', firstNode->frequency + secondNode->frequency);
			newNode->left = firstNode;
			newNode->right = secondNode;
			
			//add the newly created node to queue2
			queue2.push(newNode);
			//break if queue 2 has only one element
			if(queue1.size()==0 && queue2.size()==1)
				break;
		}
		
		//Step 3: generate codes by DFS-traversing the Huffman tree processed above. The only node left in queue2 is the tree;s root node
		generateCodesPreorder(queue2.front(), "", result);
	}
}

void huffman_encoding_sorted_input()
{
	std::vector<std::pair<char, unsigned>> input;
	
	huffman_encode_sortedInput::read_input_by_line(input);

	std::vector<std::pair<char, std::string>> result;
	huffman_encode_sortedInput::process_input(input, result);
	
	std::cout<<"inserted character    	Huffman encoding"<<std::endl;
	for(auto it = result.cbegin(), end = result.cend(); it!=end; ++it)
	{
		std::cout<<"	"<<it->first<<"			"<<it->second<<std::endl;
	}
}
