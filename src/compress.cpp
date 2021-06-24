#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitOutputStream.hpp"

using namespace std;

void print_usage(char ** argv) {
    cout << "Usage:" << endl;
    cout << "  " << argv[0] << " INFILE OUTFILE [-b]" << endl;
    cout << "Command-line flags:" << endl;
    cout << "  -b: switch to bitwise mode" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its contents,
 * and produces a compressed version in outfile.
 * For debugging purposes, uses ASCII '0' and '1' rather than bitwise I/O.
 */
void compressAscii(const string & infile, const string & outfile) {
    // TODO (checkpoint)
    ifstream in;
 
    vector<int> freqs(256, 0);
    HCTree * tree = new HCTree();
    in.open(infile, ios::binary);
   /* if(in.eof()){
      in.close();
      return;
    }*/
      if(!in.is_open()){
        in.close();
	return;	
    }
    int wordNum = 0;
    int headerCount = 0;
    int count = 0; 
    while (1) {
      count = in.get();
      if (in.eof()) {break;}
      freqs[count]++;
      headerCount++;
    }
    in.clear();

    in.seekg(0, ios::beg);

    unsigned int i=0;
    unsigned int frq;
    ofstream out;
    out.open(outfile, ios::binary);
    
    while(i!=freqs.size()){
      
      frq= freqs[i];
      if(frq > 0){
         
         wordNum++;

	}
      out<<frq<<endl;
      i++;

    }

    int symb;
    if ( headerCount > 1 && wordNum >1) {  
        tree->build(freqs);
	while(1) {
        symb =in.get(); //?
        if (in.eof()) {break;}
        tree->encode(symb, out);
      }
    }
    in.close();
    out.close();
    //cerr << "TODO: compress '" << infile << "' -> '"
        //<< outfile << "' here (ASCII)" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its contents,
 * and produces a compressed version in outfile.
 * Uses bitwise I/O.
 */
void compressBitwise(const string & infile, const string & outfile) {
    // TODO (final)
    ifstream in;
 
    vector<int> freqs(256, 0);
    HCTree * tree = new HCTree();
    in.open(infile, ios::binary);
   /* if(in.eof()){
      in.close();
      return;
    }*/
      if(!in.is_open()){
        in.close();
	return;	
    }
    int wordNum = 0;
    int headerCount = 0;
    int count = 0; 
    while (1) {
      count = in.get();
      if (in.eof()) {break;}
      freqs[count]++;
      headerCount++;
    }
    in.clear();

    in.seekg(0, ios::beg);

    unsigned int i=0;
    int frq;
    int nl = 10;

    ofstream out;
    out.open(outfile, ios::binary);
    
    while(i!=freqs.size()){
      
      frq= freqs[i];
      if(frq > 0){
         
         wordNum++;

      }
      out.write((char *) & frq, sizeof(frq));
     // out.write((char *) & nl, sizeof(nl));
      
      i++;
    }
    
  
  
    byte symb;
    if ( headerCount > 1 && wordNum >1) {  
        
        
        BitOutputStream writeB(out);
        tree->build(freqs);
	while(1) {
          symb =in.get(); 
          if (in.eof()) {break;}
          tree->encode(symb, writeB);
      }
   
     // if ( writeB.getBits() != 8 ) {//Hatef
        writeB.flush();
     // }
    }
    //tree->~HCTree();
    in.close();
    out.close();
    cerr << "TODO: compress '" << infile << "' -> '"
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
        compressBitwise(infile, outfile);
    } else {
        compressAscii(infile, outfile);
    }

    return 0;
}
