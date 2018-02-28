#include <iostream>
#include <cstring>
using namespace std;
int main() {
  char a[1001]; //除数
  int b = 0;    //被除数
  cin >> a >> b;
  int len = strlen(a);
  int num = 0;
  if(len==1) {
    cout << "0 " << a[0]-'0';
  } else {
    for(int i=0; i<len; i++) {
      if(i>0 && num==0 && a[i]-'0'<b) {
        cout << "0";
      }
      num = num*10+(a[i]-'0');
      if(num/b>0) {
        cout << num/b;
        num %= b;
      }
    }
    cout << " " << num;
  }
  return 0;
}