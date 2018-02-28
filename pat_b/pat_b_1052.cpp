#include <stdio.h>
#define pat_c_52_max 5
#define pat_c_52_maxch 11
int pat_c_52_read(char arr[][pat_c_52_max]) {
  char ch = 0;
  int count = 0;
  int n = 0;
  int flag = 0;
  do {
    scanf("%c", &ch);
    if(ch=='[' && !flag) {
      n = 0;
      flag = 1;
    } else if(ch==']' && flag) {
      arr[count++][n] = '\0';
      flag = 0;
    } else {
      arr[count][n++] = ch;
    }
  } while(ch!='\n');
  return count;
}
int main() {
  char* nstr = "Are you kidding me? @\\/@";
  char shou[pat_c_52_maxch][pat_c_52_max];
  char yan[pat_c_52_maxch][pat_c_52_max];
  char kou[pat_c_52_maxch][pat_c_52_max];
  int cs = pat_c_52_read(shou);
  int cy = pat_c_52_read(yan);
  int ck = pat_c_52_read(kou);
  int k = 0;
  int ls,ly,m,ry,rs = 0;
  scanf("%d", &k);
  for(int i=0; i<k; i++) {
    scanf("%d %d %d %d %d", &ls, &ly, &m, &ry, &rs);
    if(ls>cs || rs>cs || ly>cy || ry>cy || m>ck || ls<=0 || rs<=0 || ly<=0 || ry<=0 || m<=0) {
      printf("%s\n", nstr);
    } else {
      printf("%s(%s%s%s)%s\n", shou[ls-1],yan[ly-1],kou[m-1],yan[ry-1],shou[rs-1]);
    }
  }
  return 0;
}