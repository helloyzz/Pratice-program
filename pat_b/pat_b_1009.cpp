#include <iostream>
using namespace std;
#include <string>
#include <cstring>

int main(){  
  int sum = 0;
  string str;
  string arr[80];
  getline(cin, str);
  int len = strlen(str.c_str());
  for(int i=len-1; i>=0; i--) {
    if(str[i]==' ') {
      arr[sum++] = &str[i+1];
      str[i] = '\0';
    }
  }
  arr[sum++] = &str[0];
  for(int i=0; i<sum; i++) {
    cout << arr[i];
    if(i!=sum-1) cout << ' ';
  }
  
    return 0;  
}