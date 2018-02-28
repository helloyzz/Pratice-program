#include <stdio.h>
int main() {
  int c,e,flag = 0;
  while(scanf("%d %d", &c, &e)!=EOF) {
    if(c*e) {
      if(flag) {
        printf(" ");
      } else {
        flag = 1;
      }
      printf("%d %d", c*e, e-1);
    }
  }
  if(!flag) printf("0 0");
  return 0;
}