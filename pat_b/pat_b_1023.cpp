#include <iostream>
using namespace std;
int main(){
  int arr[10];
  for(int i=0; i<10; i++) {
    cin >> arr[i];
  }
  int f = 1;
  for(int i=1; i<10; i++) {
    if(arr[i]!=0) {
      if(f && arr[0]!=0) {
        cout << i;
        arr[i]--;
        while(arr[0]--) {
          cout << 0;
        }
        f = 0;
      }
      while(arr[i]--) {
        cout << i;
      }
    }
  }
  return 0;
}