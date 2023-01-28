
#include "Huffman.h"
using namespace std;

/**
 * Description: This function goes thru the string and keeps track
 * of the frequency of each character
 * @param input: the string that the frequency table is based off of
 * @return map<string,int> dictionary: return the freq table of type
 * map
 * @see none
 */
map<string,int> Huffman::BuildCharacterFrequencyTable(string input) {
    map<string, int> dictionary; //make a dictionary of data type map
    int length = input.length(); //make var of string length
    //iterate thru each char in input
    for(int i=0; i<length; i++){
        string currChar = input.substr(i,1); //curr char is 1 character of that input
        auto it = dictionary.find(currChar); //create iterator to find current character
        //if character already exists in dictionary, then it was found so add value to it
        //second refers to frequency of letter so if its zero it doesn't exist
        if(it->second!=0){
            dictionary[currChar]=dictionary[currChar]+1; //value at current Char adds one
        }
        else{ //if character does not exist in dictionary, make it a value
            dictionary[currChar]=1;
        }
    }
    return dictionary; //return frequency table
}

/**
 * Description: Builds the Huffman Tree that organizes the nodes
 * by frequency with use of a priority queue.
 * @param in: string that tree is based after
 * @return Node* nodes.top(): is the root of the tree
 * @see BuildCharacterFrequencyTable: helper function that will
 * create table that organizes letter's frequency
 */
Node* Huffman::HuffmanBuildTree(string in) {
    map<string,int> table = BuildCharacterFrequencyTable(in); // First build the frequency table
    // Make a priority queue of type Node called nodes
    //have to pass in class compareCount to sort queue accordingly
    priority_queue<Node*,vector<Node*>,compareCount> nodes;
    map<string, int>::iterator it; //create an iterator for the map
    for (it = table.begin(); it != table.end(); it++) {
        Node* newNode = new Node(); //create new node
        //set the letter and count of te new Node
        newNode->letter=it->first;
        newNode->count=it->second;
        nodes.push(newNode); //push node unto queue
    }
    // Make parent nodes up to the root
    //needs to stop once one node left(that is the root node)
    while (nodes.size()>1) {
        // Dequeue 2 lowest-priority nodes: left and right
        Node* left = nodes.top();
        nodes.pop();
        Node* right = nodes.top();
        nodes.pop();

        // Make a parent for the two nodes
        int frequencySum = right->count + left->count;
        Node* parent = new Node();
        //intialize values
        parent->letter="\0";
        parent->count = frequencySum;
        parent->zero = left;
        parent->one = right;

        // Enqueue parent back into priority queue
        nodes.push(parent);
    }
    //returns the final node in the queue which is the root node for the tree
    return nodes.top();
}

/**
 * Description: This Function gets the binary code for each character in the string
 * it then organizes those codes with each character in a map. This Function uses
 * recursion and its base case is when it reaches a leaf node.
 * @param node: the root of the Huffman tree
 *        prefix: the binary code of each letter
 *        output: the map of the character with corresponding code
 * @return output:  this is the map of the characters with their corresponding code
 * @see none
 */
//parameter is map<string,string> bc it is going to make a letter w associated binary like "a", "0000"
map<string, string> Huffman::HuffmanGetCodes(Node* node, string prefix, map<string,string>& output) {
    //BASE CASE if it is a leaf node
    if (node->zero == nullptr && node->one == nullptr) {
        //set the character at that leaf node to the binary combination of 0&1 (prefix)
        output[node->letter] = prefix;
    }
    //GENERAL CASE
    else {
        HuffmanGetCodes(node->zero, prefix + "0", output); //return left side
        HuffmanGetCodes(node->one, prefix + "1", output);//return right side
    }
    //return new map of characters with their associated binary equivalent (code)
    return output;
}

/**
 * Description: This function converts the english string of text into
 * a binary string of text.
 * @param input: the string to be converted to binary
 * @return result: the binary string
 * @see HuffmanBuildTree: Builds the Huffman Tree
 *      HuffmanGetCode: returns the map of each character and its frequency
 */
string Huffman::HuffmanCompress(string input) {
        // Build the Huffman tree
        Node* root = HuffmanBuildTree(input);
        // Get the compression codes from the tree
        map<string,string> codes;
        HuffmanGetCodes(root, "", codes);

        // Build the compressed result of 0&1 (code)
        string result = "";
        for(int i=0; i<input.length();i++){
            string curr = input.substr(i,1);
            //get binary equivalent to each letter
            result += codes[curr];
        }
        //return string of binary codes
        return result;
}

/**
 * Description: This function takes the binary string and converts it
 * back into English.
 * @param compressedString: the string that is in binary code
 *        treeRoot: is the root of the Huffman tree that was made
 * @return resultTXT: the english result of the text
 * @see none
 */
string Huffman::HuffmanDecompress(string compressedString, Node* treeRoot) {
    //create node that is root of the tree
    Node* node = treeRoot;
    string resultTXT = "";
    //iterate through string
    for (int i=0; i<compressedString.length();i++) {
        //current bit (0 or 1) in string
        string bit = compressedString.substr(i, 1);
        // Go to left or right child based on bit value
        if (bit == "0") { node = node->zero; }
        else { node = node->one; } //bit == 1

        // If the node is a leaf, add the character to the
        // decompressed result and reset to the root node
        if (node->zero==nullptr && node->one==nullptr) {
            resultTXT += node->letter;
            node = treeRoot;
        }
    }
    return resultTXT;
}

/**
 * Description: This function puts the contents of the .txt
 * file into a string variable
 * @param file: is the name of the .txt file
 * @return textFinal: is the string version of the .txt file
 * @see none
 */
string Huffman::TXTtoString(string file) {
    // vector that will store all the file lines
    vector<string> text;
    // string holding one line
    string line;
    // attach input stream to file
    ifstream inputFile(file);
    // status of the File upload
    string failureMessage = "file failed to open";
    if(!inputFile){return failureMessage;}

    string textFinal = "";
    // read the text line by line
    while(getline(inputFile, line))
    {
        // store each line as vector element
        text.push_back(line);
        //add the line to the textFinal
        textFinal += line;
    }
    //close the file
    inputFile.close();
    //return the .txt file as a string
    return textFinal;
}
