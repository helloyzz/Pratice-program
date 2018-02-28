#include <cstdlib>
#include <cstdio>
using namespace std;
int cmp1(const void* a, const void* b) {
  int arg1 = *static_cast<const int*>(a);
  int arg2 = *static_cast<const int*>(b);
  if(arg1>arg2) return 1;
  if(arg1<arg2) return -1;
  return 0;
}
int main() {
  int n = 0;
  scanf("%04d", &n);
  int arr[4];
  int tem=0;
  int n1=0;
  int n2=0;
  int f=n;
  if((n/1000 == n/100%10) && (n/1000 == n/10%10) && (n/1000 == n%10)) {
    printf("%04d - %04d = 0000\n", n, n);
    return 0;
  }
  do {
    for(int i=0; i<4; i++) {
      tem = f%10;
      arr[i] = tem;
      f /= 10;
    }
    qsort(arr, 4, sizeof(int), &cmp1);
    n1 = arr[3]*1000+arr[2]*100+arr[1]*10+arr[0];
    n2 = arr[0]*1000+arr[1]*100+arr[2]*10+arr[3];
    f = n1-n2;
    printf("%04d - %04d = %04d\n", n1, n2, f);
  } while(f!=6174);
  return 0;
}