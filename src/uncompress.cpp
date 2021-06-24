#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitInputStream.hpp"

using namespace std;

void print_usage(char ** argv) {
    cout << "Usage:" << endl;
    cout << "  " << argv[0] << " INFILE OUTFILE [-b]" << endl;
    cout << "Command-line flags:" << endl;
    cout << "  -b: switch to bitwise mode" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * For debugging purposes, uses ASCII '0' and '1' rather than bitwise I/O.
 */
void uncompressAscii(const string & infile, const string & outfile) {
    // TODO (checkpoint)
    unsigned int i;
    int freq;
    ifstream in;
    char symbol;
    bool notZero= false;
    int totalNum = 0;
    int oneWord =0;
    unsigned  int place = 0;
    
    in.open(infile, ios::binary);

    if(!in.is_open()){
       
       in.close();
       return;

    }
    HCTree * tree = new HCTree();
    vector<int> freqs(256, 0);
    
    for ( i = 0; i < freqs.size(); i++) {
     
	 in >> freqs[i];

      if(freqs[i]>0){
	  notZero = true;
          totalNum = totalNum + freqs[i];
          oneWord++;
          place = i;
	}
    }
    
    ofstream out;
    out.open(outfile, ios::binary);
   
     if(oneWord == 1){

        while(totalNum > 0){
          
          symbol=(char)(place);
          out<< symbol;
          totalNum--;

	}

    }
    if(notZero == true && oneWord !=1){
        tree->build(freqs);
       
   
        while(totalNum >0){
           symbol = tree->decode(in);
           out << symbol;
           totalNum--;
	}
    }
//    delete tree;
    in.close();
    out.close();
   // cerr << "TODO: uncompress '" << infile << "' -> '"
     //   << outfile << "' here (ASCII)" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * Uses bitwise I/O.
 */
void uncompressBitwise(const string & infile, const string & outfile) {
    // TODO (final)

    unsigned int i;
    //char value;
    int freq;
   // int i;
   // int freq;
    ifstream in;
    char symbol = 0;
    bool notZero= false;
    int totalNum = 0;
    int oneWord =0;
    unsigned  int place = 0;
    
    in.open(infile, ios::binary);

    if(!in.is_open()){
       
       in.close();
       return;

    }
    HCTree * tree = new HCTree();
   // HCTree tree;
    vector<int> freqs(256, 0);
    
    for ( i = 0; i < freqs.size(); i++) {
     
	// in >> freqs[i];
           //freq = in.get();
           in.read((char *) &freq, sizeof(freq));
           //cout << freq;
           //freqs[i] = (int)(value);
           freqs[i] = freq;
      if(freqs[i] > 0){
	  notZero = true;
          totalNum = totalNum + freqs[i];
          oneWord++;
          place = i;
	}
    }
    
    ofstream out;
    out.open(outfile, ios::binary);
    //out.open(outfile);
   
     if(oneWord == 1){
       
        while(totalNum > 0){
          
          symbol=(char)(place);
          out.put(symbol);
          totalNum--;

	}

    }
    if(notZero == true && oneWord !=1){
       
       BitInputStream readB(in);
       tree->build(freqs);
       
   
        while(totalNum >0){
           symbol = tree->decode(readB);
           //cout << (unsigned char)symbol;
           //out << symbol;
           out.put(symbol);
           totalNum--;
	}
    }
    
    //delete tree;
    in.close();
    out.close();
    cerr << "TODO: uncompress '" << infile << "' -> '"
        << outfile << "' here (bitwise)" << endl;
}

int main(int argc, char ** argv) {
    string infile = "";
    string outfile = "";
    bool bitwise = false;
    for (int i = 1; i < argc; i++) {
        string currentArg = argv[i];
        if (currentArg == "-b") {
            bitwise = true;
        } else if (infile == "") {
            infile = currentArg;
        } else {
            outfile = currentArg;
        }
    }

    if (infile == "" || outfile == "") {
        cout << "ERROR: Must provide input and output files" << endl;
        print_usage(argv);
        return 1;
    }

    if (bitwise) {
        uncompressBitwise(infile, outfile);
    } else {
        uncompressAscii(infile, outfile);
    }

    return 0;
}
