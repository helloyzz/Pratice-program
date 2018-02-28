#include <stdio.h>
int main() {
  char ch = 0;
  int sum = 0;
  do {
    scanf("%c", &ch);
    if(ch>='a' && ch<='z') {
      sum += ch-'a'+1;
    } else if(ch>='A' && ch<='Z') {
      sum += ch-'A'+1;
    }
  } while(ch!='\n');
  int zero = 0;
  int one = 0;
  while(sum!=0) {
    if(sum%2==0) {
      zero++;
    } else if(sum%2==1) {
      one++;
    }
    sum /= 2;
  }
  printf("%d %d", zero, one);
  return 0;
}