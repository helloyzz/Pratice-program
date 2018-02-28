#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct pat_c_42_char {
  int count;
  char ch;
};
int pat_c_42_cmp(const void* a, const void* b) {
  pat_c_42_char e1 = *static_cast<const pat_c_42_char*>(a);
  pat_c_42_char e2 = *static_cast<const pat_c_42_char*>(b);
  if(e1.count>e2.count) {
    return -1;
  } else if(e1.count==e2.count && e1.ch<e2.ch && (e1.ch!='0'&& e2.ch!='0')) {
    return -1;
  } else if(e1.count<e2.count) {
  return 1;
  }
  return 0;
}
int main() {
  char str[1001] = {-1};
  int c = 0;
  do {
  scanf("%c", &str[c]);
  } while(str[c++]!='\n');
  pat_c_42_char arr[27] = {0};
  int len = strlen(str);
  for(int i=0; i<len; i++) {
    if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z')) {
      char ch = tolower(str[i]);
    arr[ch-'a'].ch = ch;
    arr[ch-'a'].count++;
    }
  }
  qsort(arr, 27, sizeof(pat_c_42_char), &pat_c_42_cmp);
  printf("%c %d", arr[0].ch, arr[0].count);
  return 0;
}