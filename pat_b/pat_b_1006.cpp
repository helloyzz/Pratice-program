#include <iostream>
using namespace std;

int main(int argc, char** argv) {
  int n = 0;
  cin >> n;
  int b = 0;
  int s = 0;
  int g = 0;

  g = n%10;
  n /= 10;
  s = n%10;
  n /= 10;
  b = n%10;
  n /= 10;

  while(b--) {
    cout << "B";
  }
  while(s--) {
    cout << "S";
  }
  for(int i=1; i<=g; i++) {
    cout << i;
  }
  return 0;
}