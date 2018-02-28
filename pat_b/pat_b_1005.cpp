#include <iostream>
using namespace std;
#include <cstdlib>
int cmp(const void* a, const void* b) {
    int arg1 = *static_cast<const int*>(a);
    int arg2 = *static_cast<const int*>(b);

    if(arg1 < arg2) return -1;
    if(arg1 > arg2) return 1;
    return 0;
}

int main(int argc, char** argv) {
  int n = 0;
  int t = 0;
  cin >> n;
  int arr[n];
  for(int i=0; i<n; i++) {
    cin >> arr[i];
  }
  for(int i=0; i<n; i++) {
    t = arr[i];
    if(t==0) continue;
    while(t!=1) {
      if(t%2==0) {
        t /= 2;
      } else {
        t = (3*t+1)/2;
      }
      for(int j=0; j<n; j++) {
        if(t==arr[j]) {
          arr[j]=0;
          break;
        }
      }
    }
  }
  qsort(arr, n, sizeof(int), &cmp);
  for(int i=n-1; i>=0; i--) {
    if(arr[i]!=0) {
      cout << arr[i];
      if(arr[i-1]!=0) {
        cout << ' ';
      }
    }
  }
  return 0;
}