#include <iostream>
using namespace std;
int main() {
  int n = 0;
  cin >> n;
  int count = 1;
  while(n--) {
    long long a,b,c;
    cin >> a;
    cin >> b;
    cin >> c;
    if(a+b>c) {
      cout << "Case #" << count++ << ":" << " true" << endl;
    } else {
      cout << "Case #" << count++ << ":" << " false" << endl;
    }
  }

  return 0;
}