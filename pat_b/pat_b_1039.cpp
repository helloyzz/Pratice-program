#include <iostream>
#include <string>
#include <cstring>
int main() {
  std::string str1;
  std::string str2;
  std::cin >> str1;
  std::cin >> str2;
  int len1 = strlen(str1.c_str());
  int len2 = strlen(str2.c_str());
  int nf = 0;
  int f = 0;
  for(int i=0; i<len2; i++) {
    int pos = str1.find(str2[i]);
    if(pos==-1) {
      nf++;
    } else {
      f++;
      str1[pos] = '_';
    }
  }
  if(f==len2) {
    std::cout << "Yes" << " " << len1-f;
  } else {
    std::cout << "No" << " " << nf;
  }
  return 0;
}