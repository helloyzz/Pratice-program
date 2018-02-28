#include <stdio.h>
int main() {
  int n = 0;
  scanf("%d", &n);
  int jhan = 0;
  int jhua = 0;
  int yhan = 0;
  int yhua = 0;
  int jhe = 0;
  int yhe = 0;
  for(int i=0; i<n; i++) {
    scanf("%d %d %d %d", &jhan,&jhua,&yhan,&yhua);
    int tem = jhan+yhan;
    if(tem==jhua && tem!=yhua) {
      yhe++;
    } else if(tem!=jhua && tem==yhua) {
      jhe++;
    }
  }
  printf("%d %d", jhe, yhe);
  return 0;
}