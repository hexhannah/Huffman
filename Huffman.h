#include<string>
#include<queue>
#include<map>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;

//class definition of Node ADT
#ifndef NODE
#define NODE
struct Node{
    string letter;
    int count;
    Node* zero = nullptr;
    Node* one = nullptr;
};
#endif

//class to program priority queue
#ifndef COMPARECOUNT
#define COMPARECOUNT
struct compareCount{
    bool operator()(Node* const& lhs, Node* const& rhs){
        return lhs->count > rhs->count;
    }
};
#endif

//huffman class of all its methods
#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H
class Huffman{
public:
    map<string,int> BuildCharacterFrequencyTable(string input);
    Node* HuffmanBuildTree(string input);
    map<string,string> HuffmanGetCodes(Node* node, string prefix, map<string,string>& output);
    string HuffmanCompress(string input);
    string HuffmanDecompress(string compressedString, Node* treeRoot);
    string TXTtoString(string file);
private:

};

#endif //HUFFMAN_HUFFMAN_H
