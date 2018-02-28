#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int main(){
  bool table[128] = {0};
  string str1;
  string str2;
  cin >> str1;
  cin >> str2;
  int len = strlen(str1.c_str());
  int c1 = 0;
  int c2 = 0;
  for(int i=0; i<len; i++) {
    if(str1[c1]!=str2[c2] && table[str1[c1]]==0) {
      if(str1[c1]>='A' && str1[c1]<='Z') {
        table[str1[c1]+32] = 1;
        cout << str1[c1];
      } else if(str1[c1]>='a' && str1[c1]<='z') {
        table[str1[c1]-32] = 1;
        cout << char(str1[c1]-32);
      } else {
        cout << str1[c1];
      }
      table[str1[c1]] = 1;
      c1++;
    } else if(str1[c1]!=str2[c2] && table[str1[c1]]==1) {
      c1++;
    } else {
      c1++;
      c2++;
    }
  }
}