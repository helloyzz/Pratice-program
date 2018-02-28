#include <iostream>
#include <new>
int main() {
  int n = 0;
  std::cin >> n;
  int num = 0;
  int score = 0;
  int* school = new int[n];
  for(int i=0; i<n; i++) {
    school[i] = 0;
  }
  int max_n = 0;
  int max_s = -1;
  for(int i=0; i<n; i++) {
    std::cin >> num;
    std::cin >> score;
    school[num] += score;
    if(school[num]>max_s) {
      max_n = num;
      max_s = school[num];
    }
  }
  std::cout << max_n << " " << max_s << std::endl;
  return 0;
}