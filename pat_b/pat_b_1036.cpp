#include <iostream>
int main() {
  int n = 0;
  std::cin >> n;
  char c;
  std::cin >> c;
  for(int i=1; i<=(n+1)/2; i++) {
    if(i==1 || i==(n+1)/2) {
      for(int j=0; j<n; j++) {
        std::cout << c;
      }
    } else {
      std::cout << c;
      for(int j=0; j<n-2; j++) {
        std::cout << " ";
      }
      std::cout << c;
    }
    std::cout << std::endl;
  }
  return 0;
}