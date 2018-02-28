#include <iostream>
#include <cstdlib>
#include <new>
using namespace std;
int cmp4(const void* a, const void* b) {
  long long arg1 = *static_cast<const long long*>(a);
  long long arg2 = *static_cast<const long long*>(b);
  if(arg1>arg2) {
    return 1;
  } else if(arg1<arg2) {
    return -1;
  }
  return 0;
}
int main() {
  int n = 0;
  cin >> n;
  long long p = 0;
  cin >> p;long long* arr = new long long[100001];
  for(int i=0; i<n; i++) {
    cin >> arr[i];
  }
  qsort(arr, n, sizeof(long long), &cmp4);
  int c = 0;
  for(int i=0; i<n; i++) {
    for(int j=i+c; j<n; j++) {
      if(arr[j]>arr[i]*p) break;
      if(j-i+1>c) c = j-i+1;
    }
  }
  cout << c << endl;
  return 0;
}