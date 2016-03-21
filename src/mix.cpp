//in mix.cpp

#include "mix.h"

unsigned long mix(unsigned long a, unsigned long b, unsigned long c) {
  /*
   Robert Jenkins' 96 bit Mix Function
   Found: http://stackoverflow.com/questions/322938/recommended-way-to-initialize-srand
   Source 1: http://web.archive.org/web/20070111091013/http://www.concentric.net/~Ttwang/tech/inthash.htm
   Source 2: http://burtleburtle.net/bob/hash/doobs.html
   */
  a=a-b;  a=a-c;  a=a^(c >> 13);
  b=b-c;  b=b-a;  b=b^(a << 8);
  c=c-a;  c=c-b;  c=c^(b >> 13);
  a=a-b;  a=a-c;  a=a^(c >> 12);
  b=b-c;  b=b-a;  b=b^(a << 16);
  c=c-a;  c=c-b;  c=c^(b >> 5);
  a=a-b;  a=a-c;  a=a^(c >> 3);
  b=b-c;  b=b-a;  b=b^(a << 10);
  c=c-a;  c=c-b;  c=c^(b >> 15);
  return c;
}
