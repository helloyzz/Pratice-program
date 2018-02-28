#include <cstdio>
using namespace std;
#define CLK_TCK 100
int main(){
  int c1 = 0;
  int c2 = 0;
  scanf("%d %d", &c1, &c2);
  int sub = c2-c1;
  if(sub%CLK_TCK>=50) {
    sub = sub/100 + 1;
  } else {
    sub = sub/100;
  }
  printf("%02d:%02d:%02d", sub/3600, sub%3600/60, sub%60);
  return 0;
}