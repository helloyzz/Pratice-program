#include <cstring>
#include <cstdio>
using namespace std;
int main(){
  char str[1001];
  scanf("%s", str);
  int len = strlen(str);
  int arr[10] = {0};
  for(int i=0; i<len; i++) {
    switch(str[i]) {
      case '0':
        arr[0]++;
        break;
      case '1':
        arr[1]++;
        break;
      case '2':
        arr[2]++;
        break;
      case '3':
        arr[3]++;
        break;
      case '4':
        arr[4]++;
        break;
      case '5':
        arr[5]++;
        break;
      case '6':
        arr[6]++;
        break;
      case '7':
        arr[7]++;
        break;
      case '8':
        arr[8]++;
        break;
      case '9':
        arr[9]++;
        break;
    }
  }
  for(int i=0; i<10; i++) {
    if(arr[i]!=0) {
      printf("%d:%d\n", i, arr[i]);
    }
  }
    return 0;  
} 