#include "BitOutputStream.hpp"

// TODO (final)
BitOutputStream::BitOutputStream(ostream & o) : out(o) {
  buff = 0;
  nbits = 0;
  //nthChar = 0;//Hatef
}

/*int BitOutputStream::getBits() const {//Hatef
   return nbits;
}*/
void BitOutputStream::writeBit(bool bit) {
     
  if(nbits == 8){
    this->flush();
    //buff = buff | ( bit << (7 - nbits));
    
  }
 // else{
   if ( nbits < 8 ) {
         buff = buff | ( bit << (7 - nbits));
         nbits++;
  
	}
 // }
 /* if(nbits == 8){
    this->flush();
    buff = buff | ( bit << (7 - nbits));
    
  }*/
    // TODO (final)
}

void BitOutputStream::flush() {
    // TODO (final)
    this->out.write((char *)(&buff), sizeof(buff));
    buff = 0;
    nbits = 0;
}

