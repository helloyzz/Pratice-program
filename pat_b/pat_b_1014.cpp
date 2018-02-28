using namespace std;
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
int main() {
  char arr[4][65];
  int count = 0;
  for(int i=0; i<4; i++) {
    scanf("%s", arr[i]);
  }
  int len1 = strlen(arr[0]);
  for(int i=0; i<len1; i++) {
    if(arr[0][i]>='A' && arr[0][i]<='G' && arr[0][i]==arr[1][i] && count==0) {
      switch(arr[0][i]) {
        case 'A':
            printf("MON ");
            break;
        case 'B':
            printf("TUE ");
            break;
        case 'C':
            printf("WED ");
            break;
        case 'D':
            printf("THU ");
            break;
        case 'E':
            printf("FRI ");
            break;
        case 'F':
            printf("SAT ");
            break;
        case 'G':
            printf("SUN ");
            break;
      }
      count++;
      continue;
    }
    if(((arr[0][i]>='A' && arr[0][i]<='N') || (arr[0][i]>='0' && arr[0][i]<='9')) && arr[0][i]==arr[1][i] && count==1) {
      if(arr[0][i]>='0' && arr[0][i]<='9') {
        printf("0%d:", (arr[0][i]-'0'));
      } else {
        int tem = (arr[0][i]-'A')+10;
        printf("%d:", tem);
      }
      break;
    }
  }
  int len2 = strlen(arr[2]);
  for(int i=0; i<len2; i++) {
    if(((arr[2][i]>='A' && arr[2][i]<='Z') || (arr[2][i]>='a' && arr[2][i]<='z')) && arr[2][i]==arr[3][i]) {
      if(i<=9) {
        printf("0%d", i);
      } else {
        printf("%d", i);
      }
      break;
    }
  }
  return 0;
}