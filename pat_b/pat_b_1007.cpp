#include <iostream>
using namespace std;

int main(int argc, char** argv) {
  int n = 0;
  cin >> n;
  int sum = 0;
  int count = 0;
  int flag = 0;
  int arr[100000] = {0};
  for(int i=3; i<100001; i+=2) {
    flag = 0;
    for(int j=3; j*j<=i; j+=2) {
      if(i%j==0) {
        flag = 1;
      }
    }
    if(!flag) arr[count++] = i;
  }
  for(int i=1; arr[i]<=n; i++) {
    if(arr[i]-arr[i-1]==2) sum++;
  }
  cout << sum << endl;
  return 0;
}