#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int main(){
  string str; //科学计数法
  cin >> str;
  int len = strlen(str.c_str());
  int pos = str.rfind("E");
  str[pos++] = '\0';
  int mov = 0;
  int f = 0;
  while(pos<len) {
    if(str[pos]=='0' && mov==0) {
      pos++;
      continue;
    } else if(str[pos]=='-') {
      pos++;
      f = -1;
    } else if(str[pos]=='+') {
      pos++;
      f = 1;
    } else {
      mov = mov*10+(str[pos++]-'0');
    }
  }
  if(str[0]=='-') {
    cout << "-";
  }
  int c = 1;
  if(f==-1) {
    mov--;
    cout << "0.";
    while(mov--) {
      cout << "0";
    }
    while(str[c]!='\0') {
      if(str[c]=='.') {
        c++;
        continue;
      }
      cout << str[c++];
    }
  } else if(f==1) {
    cout << str[c++];
    c++;
    while(mov--) {
      if(str[c]=='\0') {
        cout << "0";
      } else {
        cout << str[c++];
      }
    }
    if(str[c]!='\0') {
      cout << ".";
      while(str[c]!='\0') {
        cout << str[c++];
      }
    }
  }
  return 0;
}