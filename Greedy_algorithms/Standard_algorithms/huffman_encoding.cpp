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
