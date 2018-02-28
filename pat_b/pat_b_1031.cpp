#include <iostream>
#include <string>
int main(){
  int power[17] = {7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
  char M[12] = {'1','0','X','9','8','7','6','5','4','3','2'};
  int n = 0;
  int sum = 0;
  int count = 0;
  std::cin >> n;
  std::string id;
  for(int i=0; i<n; i++) {
    std::cin >> id;
    for(int j=0; j<17; j++) {
      if(id[j]>='0' || id[j]<='9') {
        sum += (id[j]-'0')*power[j];
      } else if(id[j]=='X') {
        sum += 0;
      }
    }
    sum %= 11;
    if(M[sum]!=id[17]) {
      std::cout << id << std::endl;
    } else {
      count++;
    }
    sum = 0;
  }
  if(count==n) std::cout << "All passed" << std::endl;
  return 0;
}