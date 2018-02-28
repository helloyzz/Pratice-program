#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  int n,m = 0;
  scanf("%d %d", &n, &m);
  int* fscore = (int*)malloc(sizeof(int)*m);
  memset(fscore, 0, sizeof(int)*m);
  int* snum = (int*)malloc(sizeof(int)*m);
  memset(snum, 0, sizeof(int)*m);
  char** arr = (char**)malloc(sizeof(char*)*m);
  memset(arr, 0, sizeof(char*)*m);
  for(int i=0; i<m; i++) {
    arr[i] = (char*)malloc(7);
    memset(arr[i], 0, 7);
  }
  for(int i=0; i<m; i++) {
    scanf("%d %d ", &fscore[i], &snum[i]);
    int c = 0;
    char ch = 0;
    while(scanf("%c", &ch)!=EOF) {
      if(ch=='\n') break;
      if(ch==' ') continue;
      arr[i][c++] = ch;
    }
    arr[i][c] = '\0';
  }
  int* stscore = (int*)malloc(sizeof(int)*n);
  memset(stscore, 0, sizeof(int)*n);
  int* etopic = (int*)malloc(sizeof(int)*m);
  memset(etopic, 0, sizeof(int)*m);
  for(int i=0; i<n; i++) {
    char ch = 0;
    for(int j=0; j<m; j++) {
      char str[7] = {0};
      int c = 0;
      while(scanf("%c", &ch)!=EOF) {
        if(ch==')') break;
        if(ch=='(' || ch==' ') continue;
        str[c++] = ch;
      }
      str[c] = '\0';
      if(!memcmp(arr[j], str, strlen(arr[j]))) {
        stscore[i] += fscore[j];
      } else {
        etopic[j]++;
      }
    }
    scanf("%c", &ch);
  }
  for(int i=0; i<n; i++) {
    printf("%d\n", stscore[i]);
  }
  int err = 0;
  for(int i=1; i<m; i++) {
    if(etopic[i]>etopic[err]) err = i;
  }
  if(etopic[err]!=0) {
	  printf("%d %d", etopic[err], err+1);
	  for(int i=0; i<m; i++) {
			  if(etopic[i]==etopic[err] && i!=err) printf(" %d", i+1);
	  }
  } else {
	  printf("Too simple");
  }
  return 0;
}