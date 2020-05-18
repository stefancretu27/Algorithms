#include "standard_greedy_algorithms.hpp"

/*
 * Huffman encoding
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
 * 				- is the initially created nodes (those containing the input characters) are poped and added as children to the newly created nodes, at the end they will all be leaf nodes in the HUffman tree 
 *           
 * 			 Step 3 (assign codes): Once the binary tree is built, traverse it in preorder: check root if it has a character stored, then recursively do the same for left child, then for right child 
 * (root->left->right approach)
 * 				- maintain an auxiliary array. When traversing a left node, push 0 to this vector, and push 1 when traversing a right node. If the node contains a character, print the character and the values stored in
 * the vector. It shows the bit sequence encoding for that character
 * 
 * Huffman decoding
 * Problem description: given a sequence of bits and the afferent Huffman tree, decode the text which is encoded by the gien bit sequence
 * 
 * Approach: Start from the root of the tree (stored in a local variable)
 * 			 Then, for each value in the bit sequence, check if it is 0 or 1. If 0, then go to left child , if 1 go the right child. Recall all characters are only stored in leaf nodes.
 * 			 If a leaf node is reached (both children are null), the current node use for tree traversial is reset to root. Also, the character contained by the node is appended to answer.
 */ 

namespace huffman
{
	using namespace std;
	
	enum class TreeLeaf
	{	
		NONE,
		LEFT,
		RIGHT
	};
	
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
	
	void encodePreorder(const shared_ptr<MinHeapNode>& root, const string& bits, vector<pair<char, string>>& result)
	{
		if(root == nullptr)
			return;
		
		if(root->character != ' ')
		{	
			//cout<<"inserted character: "<<root->character<<"  Huffman encoding: "<<bits<<endl;
			result.push_back(make_pair(root->character, bits));
		}
		encodePreorder(root->left, bits+"0", result);
		encodePreorder(root->right, bits+"1", result);
	}
	
	void decode(const shared_ptr<MinHeapNode>& root, const string& bit_seq, string &result)
	{
		shared_ptr<MinHeapNode> current_node = root;
		
		cout<<current_node->frequency<<" "<<bit_seq.size()<<endl;
		
		for(size_t idx{0}, dim = bit_seq.size(); idx < dim; ++idx)
		{
			if(bit_seq[idx] == '0')
			{
				current_node = current_node->left;
			}
			else
			{
				current_node = current_node->right;
			}
			
			//check if leaf node
			if(current_node->left == nullptr && current_node->right==nullptr)
			{
				result.push_back(current_node->character);
				//reset current node, so next iteration starts from the root
				current_node = root;
			}
		}
	}

	void encode_decode(std::vector<std::pair<char, unsigned>>& input, vector<pair<char, string>>& encode_result, string& decoding_result)
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
		
		//Step 3: generate codes by DFS-traversing the Huffman tree processed above
		string bit_seq{};
		encodePreorder(minHeap.top(), bit_seq, encode_result);
		
		for(auto it = encode_result.cbegin(), end = encode_result.cend(); it!=end; ++it)
		{
			bit_seq.append(it->second);
		}
		
		decode(minHeap.top(), bit_seq, decoding_result);
	}
}

void huffman_encoding_and_decoding()
{
	std::vector<std::pair<char, unsigned>> input;
	
	huffman::read_input_by_line(input);

	std::vector<std::pair<char, std::string>> encoding_result;
	std::string decoding_result;
	huffman::encode_decode(input, encoding_result, decoding_result);
	
	std::cout<<"inserted character    	Huffman encoding"<<std::endl;
	for(auto it = encoding_result.cbegin(), end = encoding_result.cend(); it!=end; ++it)
	{
		std::cout<<"	"<<it->first<<"			"<<it->second<<std::endl;
	}
	
	std::cout<<"Huffman decoding"<<std::endl;
	std::cout<<decoding_result<<std::endl;

}
