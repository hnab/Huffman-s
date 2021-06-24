#include "BitInputStream.hpp"

// TODO (final)
BitInputStream::BitInputStream(istream & i) : in(i) {
   //in.read((char *)(&buff), sizeof(buff));

   buff = in.get();
   if (in.eof()){ buff = 0;}
   nbits = 0;
}

/*int BitInputStream::getBits() const {
   return nbits;
}*/
bool BitInputStream::readBit() {
  //in >> buff;
  //bool bit = (buff >> (7- nbits))<< 7 ;
  //nbits++;
 
  //return buff;  // TODO (final)

  if(nbits == 8){
    nbits = 0;
    buff = 0;
    //in >> buff;
    //in.read((char *)(&buff), sizeof(buff));
    buff = in.get();
    //if (in.eof()){ buff = 0; }
  }

  bool bit = (buff & ( 1 << (7 - nbits))) >> ( 7 - nbits );
 
  //bool bit = (buff & ( 1 << (7 - nbits)));
  nbits++;
 /* if(nbits == 8){
     buff = 0;
     nbits = 0;
0}*/
  
  return bit;
  
}
