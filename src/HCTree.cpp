#include <stack>
#include <queue>

#include "HCTree.hpp"

/**
 * Destructor for HCTree
 */
HCTree::~HCTree() {

  /* unsigned int i = 0;
  for ( i = 0; i < leaves.size(); i++) {
    delete leaves[i];
  }*/
  deleteAll(root);
  leaves.clear();
 // leaves.erase(leaves.begin(), leaves.size()-1);
 
    // TODO (checkpoint)
}

/** Use the Huffman algorithm to build a Huffman coding tree.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the tree,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs) {
    // TODO (checkpoint)
    unsigned int i = 0;
    byte parentSymbol;
    std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> pq;
   
    if (root != nullptr) {
      this->~HCTree();
      return;
    }
    for ( i = 0; i < freqs.size(); i++) {
      if ( freqs[i] != 0 ) {
        HCNode * node = new HCNode(freqs.at(i),(byte) i, 0, 0 ,0);
        this->leaves[i] = node;
        pq.push(node);
      }    
    }
    
    HCNode *parent;
   /* if ( pq.size() == 1 ) {
      root = pq.top();
      return;
    }*/
    while ( pq.size() > 1 ) {
      HCNode * first = pq.top();
      pq.pop(); 
      HCNode * second = pq.top();
      pq.pop();
      int parentCount = first->count + second->count;
      if ( first->symbol < second->symbol) {
        parentSymbol = second->symbol;
       }
      else {
        parentSymbol = first->symbol;
      }
      parent = new HCNode(parentCount, parentSymbol, first, second, 0);
      second->p = parent;
      first->p = parent;
      pq.push(parent);
    }
    root = parent;
}

/**
 *Do a post order traversal to delete nodes.
 */
 void HCTree::deleteAll(HCNode *node){

   if(node == nullptr){

     return;

  }
  deleteAll(node->c0);
  deleteAll(node->c1);
  delete node;

}

/** Write to the given ostream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, ostream& out) const {
    // TODO (checkpoint)
    /*unsigned int i;
    for ( i = 0; i < leaves.size(); i++) {
      out << leaves[i]->count << endl;
    }*/
    unsigned int index = (unsigned int) symbol;
    HCNode* curr = leaves[index];
    vector<int> code;
    while ( curr->p != nullptr ) {
      if ( curr == curr->p->c0){
        code.push_back(0);
      }
      else {
        code.push_back(1);
      }
      curr = curr->p;
    }
    for ( int i = (code.size() - 1); i >= 0; i-- ) {
      out << code[i];
    }
}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the istream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(istream& in) const {
    HCNode* node = root;
    //HCNode* prev = root;
    byte nextChar;
    if ( node->c0 == nullptr && node->c1 == nullptr){
      in >>nextChar; 
    } 
    while( node->c1 != nullptr && node->c0 != nullptr ) {
      in >> nextChar;
      
     // if(in.eof()){break;}
      //prev = node;
      if( nextChar == '0') {
        node = node->c0;
      }
      else {
        node = node->c1;
      }
    }
    return node->symbol;  // TODO (checkpoint)
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    // TODO (final)
    unsigned int index = (unsigned int) symbol;
    HCNode* curr = leaves[index];
    vector<int> code;
    while ( curr->p != nullptr ) {
      if ( curr == curr->p->c0){
        code.push_back(0);
      }
      else {
        code.push_back(1);
      }
      curr = curr->p;
    }
   
    for ( int i = (code.size() - 1); i >= 0; i-- ) {
     /* if ( out.nbits == 8 ) {
        
        out.flush();
      }*/
   
     
      if(code[i]==1){
	out.writeBit(1);
      }
      else {
	out.writeBit(0);
      }
      
     /* if(i == code.size()-1 &&  i%8 !=0){

         out.flush();

      }*/

    }
   /* if(out.nbits != 8) {
      out.flush();
    }*/
   
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(BitInputStream& in) const {
   
    HCNode* node = root;
    bool nextBit = true;
    if ( node->c0 == nullptr && node->c1 == nullptr){
        nextBit = in.readBit(); 
    } 
    while( node->c1 != nullptr && node->c0 != nullptr ) {
      
        nextBit =  in.readBit();
      
      if( nextBit == false ) {
        node = node->c0;
      }
      else {
        node = node->c1;
      }
    }
    
  return node->symbol;  // TODO (final)
}

/**
 * Print the contents of a tree
 */
void HCTree::printTree() const {
    cout << "=== PRINT TREE BEGIN ===" << endl;
    printTreeHelper(root);
    cout << "=== PRINT TREE END =====" << endl;
}

/**
 * Recursive helper function for printTree
 */
void HCTree::printTreeHelper(HCNode * node, string indent) const {
    if (node == nullptr) {
        cout << indent << "nullptr" << endl;
        return;
    }

    cout << indent << *node << endl;
    if (node->c0 != nullptr || node->c1 != nullptr) {
        printTreeHelper(node->c0, indent + "  ");
        printTreeHelper(node->c1, indent + "  ");
    }
}
