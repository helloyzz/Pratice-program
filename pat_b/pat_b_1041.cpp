#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Examine {
  char admcard[15];
  int tm;
  int em;
};
int cmp(const void* a, const void* b) {
  Examine e1 = *static_cast<const Examine*>(a);
  Examine e2 = *static_cast<const Examine*>(b);
  if(e1.tm>e2.tm) {
    return 1;
  } else if(e1.tm<e2.tm) {
    return -1;
  }
  return 0;
}
int main() {
  int n = 0;
  scanf("%d", &n);
  Examine exa[1001] = {0};
  for(int i=0; i<n; i++) {
    scanf("%s", exa[i].admcard);
    scanf("%d", &exa[i].tm);
    scanf("%d", &exa[i].em);
  }
  qsort(exa, n, sizeof(Examine), &cmp);
  int m = 0;
  scanf("%d", &m);
  int s[1001] = {-1};
  for(int i=0; i<m; i++) {
    scanf("%d", &s[i]);
  }
  for(int i=0; i<m; i++) {
    printf("%s ", exa[s[i]-1].admcard);
    printf("%d\n", exa[s[i]-1].em);
  }
  return 0;
}