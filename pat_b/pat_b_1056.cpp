#include <stdio.h>
int main() {
  int n = 0;
  scanf("%d", &n);
  int arr[n] = {0};
  for(int i=0; i<n; i++) {
    scanf("%d", &arr[i]);
  }
  int sum = 0;
  for(int i=0; i<n; i++) {
    int t = n-1;
    while(t>=0) {
      if(t==i) {
        t--;
        continue;
      }
      sum += arr[i]*10+arr[t];
      t--;
    }
  }
  printf("%d", sum);
  return 0;
}