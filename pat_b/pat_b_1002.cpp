#include <iostream>
using namespace std;
#include <cstring>

template <class T>
void m_swap(T& t1, T& t2) {
  T temp = t1;
  t1 = t2;
  t2 = temp;
}

void swap_str(char* arr, int len) {
  int start = 0;
  int end = len-1;  
  while(start<end) {
    m_swap(arr[start], arr[end]);
    start++;
    end--;
  }
}

char* m_itoa(const int num, char* arr) {
  int temp = num;
  int k = 0;
  while(temp) {
    arr[k++] = temp%10+48;
    temp = temp/10;
  }
  swap_str(arr, k);
  return arr;
}

int main(int argc, char** argv) {
  char arr[110];
  cin >> arr;
  
  int sum = 0;
  int len = strlen(arr);
  for(int i=0; i<len; i++) {
    sum += int(arr[i])-48;
    arr[i] = '\0';
  }
  m_itoa(sum, arr);
  len = strlen(arr);
  for(int i=0; i<len; i++) {
    switch(arr[i]) {
      case '0':  cout << "ling";
            break;
      case '1':  cout << "yi";
            break;
      case '2':  cout << "er";
            break;
      case '3':  cout << "san";
            break;
      case '4':  cout << "si";
            break;
      case '5':  cout << "wu";
            break;
      case '6':  cout << "liu";
            break;
      case '7':  cout << "qi";
            break;
      case '8':  cout << "ba";
            break;
      case '9':  cout << "jiu";
            break;
    }
    if(i!=len-1) cout << ' ';
  }
    cout << endl;
  return 0;
}