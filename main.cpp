#include <iostream>
#include<string>
#include"Huffman.h"
using namespace std;

int main() {
    //create object Huffman
    Huffman test;
    //string of text
    string text;
    //choice of compression
    string compressOrDecompress;
    cout << "Welcome. Here we can Compress or Decompress any file!"<<endl;
    cout << "Are you Compressing or Decompressing today? (Enter 'Compress' or 'Decompress'): "<<endl;
    cin >> compressOrDecompress;

    if(compressOrDecompress == "compress" || compressOrDecompress == "Compress"){
        cout << "What file do you want to compress?"<<endl;
        cout << "Enter the number corresponding to the desired file" <<endl;
        cout << "100west.txt (1), big.txt (2), gogogophers.txt (3), MOBY-DICK.txt (4), Shakespeare.txt (5)" << endl;
        int fileChoice;
        cout << "Enter:";
        cin >> fileChoice;
        string file;
        //file path and name for each choice
        if(fileChoice==1){file = "text_files/100west.txt";}
        else if(fileChoice==2){file = "text_files/big.txt";}
        else if(fileChoice==3){file = "text_files/gogogophers.txt";}
        else if(fileChoice==4){file = "text_files/MOBY-DICK.txt";}
        else{file = "text_files/Shakespeare.txt";}

        //make ifstream to write to file
        ifstream inputFile(file);
        //convert text from file into string
        text = test.TXTtoString(file);
        string result1 = test.HuffmanCompress(text);

        //output results into compressesd results
        ofstream out("text_files/compressedResults.txt");
        out << result1;
        out.close();
        cout << "Check 'compressedResults.txt' for your compressed text!";
    }
    //decompression
    else if(compressOrDecompress == "decompress" || compressOrDecompress == "Decompress") {
        cout<<"What file do you want to decompress (that is currently in compressResults.txt)?" <<endl;
        cout << "100west.txt (1), big.txt (2), gogogophers.txt (3), MOBY-DICK.txt (4), Shakespeare.txt (5)" << endl;
        int fileChoice;
        cout << "Enter:";
        cin >> fileChoice;
        string txt_file;
        //set file choice to the file directory
        if(fileChoice==1){txt_file = "text_files/100west.txt";}
        else if(fileChoice==2){txt_file = "text_files/big.txt";}
        else if(fileChoice==3){txt_file = "text_files/gogogophers.txt";}
        else if(fileChoice==4){txt_file = "text_files/MOBY-DICK.txt";}
        else{txt_file = "text_files/Shakespeare.txt";}

        //consent in case made a mistake
        string answeryn;
        cout << "Confirming you want to decompress 'compressedResults.txt'? (Yes/No) "<<endl;
        cin >> answeryn;
        if(answeryn=="yes" || answeryn == "Yes" || answeryn == "y" || answeryn == "Y") {
            //read in results.txt as a string then sent into decompress
            string file = "text_files/compressedResults.txt";
            //file: file we want to turn into text
            ifstream inputFile(file);
            //ctext: going to be compressed file look like 0100110
            string ctext = test.TXTtoString(file);

            //txt_file: name of original txt
            ifstream inFile(txt_file);
            //original file the .txt
            string originalFile = test.TXTtoString(txt_file);
            //build and decompress
            Node *testNode = test.HuffmanBuildTree(originalFile);
            string result2 = test.HuffmanDecompress(ctext, testNode);
            //output results in .txt file
            ofstream out("text_files/decompressedResults.txt");
            out << result2;
            out.close(); //close file
            cout << "Check 'decompressedResults.txt' for your decompressed text!";
        }
        else{ //said no to decompressing the file
            cout << "Commitment issues? Its ok, just run the program again...";
        }
    }
    else{ //misspelling somewhere in code
        cout << "Wow you suck at following directions, run the program to try again."<<endl;
    }

//Uncomment the code below to be able to use the code with user inputted string

//    string text;
//    cout << "Enter a string: ";
//    cin >> text;
//    Huffman test;
//    //making this bc decompress needs node parameter
//    //should make the same tree as the one made in the compress function
//    Node* testNode = test.HuffmanBuildTree(text);
//    string result1 = test.HuffmanCompress(text);
//    cout << result1 << endl;
//    cout << "end of compressed text\n" << endl;
//    string result2 = test.HuffmanDecompress(result1,testNode);
//    cout << "Original string: "<< text<<endl;
//    cout << "String after compression and decompression: "<<result2<<endl<<endl;
//
//    if(text==result2){
//        cout << "Success";
//    }
//    else{
//        cout << "Fail";
//    }



}
