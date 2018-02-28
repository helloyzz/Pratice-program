#include <stdio.h>
int main() {
  int n = 0;
  scanf("%d", &n);
  double num = 0;
  double sum = 0;
  for(int i=0; i<n; i++) {
    scanf("%lf", &num);
    sum += num*(n-i)*(i+1);
  }
  printf("%.2lf", sum);
  return 0;
}