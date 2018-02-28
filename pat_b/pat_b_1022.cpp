#include <cstdio>
using namespace std;
int main() {
  int a = 0;
  int b = 0;
  int d = 0;
  scanf("%d %d %d", &a, &b, &d);
  int sum = a+b;
  char res[100];
  int c = 0;
  int tem = 0;
  if(!sum) {
    printf("%d", sum);
  }
  while(sum) {
    tem = sum%d;
    res[c++] = tem+'0';
    sum /= d;
  }
  for(int i=c-1; i>=0; i--) {
    printf("%c", res[i]);
  }
  return 0;
}