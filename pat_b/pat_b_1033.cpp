#include <stdio.h>
int main() {
  int arr[130] = {0};
  char ch = 0;
  int flag = 0;
  while((ch=getchar())!='\n') {
    if(ch>='A' && ch<='Z') arr[ch-'A'+'a'] = 1;
    arr[ch] = 1;
  }
  if(arr['+']==1) {
    for(int i='A'; i<='Z'; i++) arr[i] = 1;
  }
  while((ch=getchar())!='\n') {
    if(arr[ch]) continue;
    printf("%c", ch);
    flag = 1; 
  }
  if(!flag) printf("\n");
  return 0;
}