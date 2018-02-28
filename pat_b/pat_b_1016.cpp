#include <iostream>
using namespace std;
int main() {
  long long A = 0;
  int DA = 0;
  long long B = 0;
  int DB = 0;
  long long PA = 0;
  long long PB = 0;
  cin >> A;
  cin >> DA;
  cin >> B;
  cin >> DB;
  int ca = 0;
  int cb = 0;
  while(A!=0) {
    if(A%10==DA) {
      ca++;
    }
    A /= 10;
  }
  while(B!=0) {
    if(B%10==DB) {
      cb++;
    }
    B /= 10;
  }
  for(int i=ca; i>0; i--) {
    int tem = 1;
    for(int j=1; j<i; j++) {
      tem *= 10;
    }
    PA += DA*tem;
  }
  for(int i=cb; i>0; i--) {
    int tem = 1;
    for(int j=1; j<i; j++) {
      tem *= 10;
    }
    PB += DB*tem;
  }
  cout << (PA+PB);
  return 0;
}