#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  int n = 0;
  scanf("%d", &n);
  int* arr = (int*)malloc(sizeof(int)*1001);
  memset(arr, 0, sizeof(int)*1001);
  int max = 0;
  int num = 0;
  int tm,mem,sc = 0;
  for(int i=0; i<n; i++) {
    scanf("%d-%d %d", &tm, &mem, &sc);
    arr[tm] += sc;
    if(arr[tm]>max) {
      max = arr[tm];
      num = tm;
    }
  }
  printf("%d %d", num, max);
  return 0;
}