#include <cstdio>
int find_prime(int n) {
  for(int i=2; i*i<=n; i++) {
    if(n%i==0) {
      return 0;
    }
  }
  return 1;
}
int main() {
  int m = 0;
  int n = 0;
  scanf("%d %d", &m, &n);
  int i = 2;
  int j = 0;
  int cnt = 0;
  while(1) {
    if(find_prime(i)) {
      j++;
      if(j>=m && j<n) {
        cnt++;
        if(cnt%10 == 0)
          printf("%d\n",i);   
        else
          printf("%d ",i);
      }
      if(j==n) {
        printf("%d",i);
        break;
      }        
    }
    i++;
  }
  return 0;
}