#include <stdio.h>
int main() {
  char ch = 0;
  int cP = 0;
  int cA = 0;
  int cT = 0;
  int ce = 0;
  int cs = 0;
  int ct = 0;
  do {
    scanf("%c", &ch);
    switch(ch) {
      case 'P':
        cP++;
        break;
      case 'A':
        cA++;
        break;
      case 'T':
        cT++;
        break;
      case 'e':
        ce++;
        break;
      case 's':
        cs++;
        break;
      case 't':
        ct++;
        break;
    }
  } while(ch!='\n');
  while(cP>0 || cA>0 || cT>0 || ce>0 || cs>0 || ct>0) {
    if(cP-->0) printf("P");
    if(cA-->0) printf("A");
    if(cT-->0) printf("T");
    if(ce-->0) printf("e");
    if(cs-->0) printf("s");
    if(ct-->0) printf("t");
  }
  return 0;
}