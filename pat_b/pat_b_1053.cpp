#include <stdio.h>
int main() {
  int n = 0;
  float ls = 0;
  int d = 0;
  scanf("%d %f %d", &n, &ls, &d);
  int k = 0;
  int p_vacant = 0;
  int vacant = 0;
  int resident = 0;
  for(int i=0; i<n; i++) {
    scanf("%d", &k);
    int ct = 0;
    float ec = 0;
    for(int j=0; j<k; j++) {
      scanf("%f", &ec);
      if(ec<ls) ct++;
    }
    if(ct>(k/2) && k>d) {
      vacant++;
    } else if(ct>(k/2)) {
      p_vacant++;
    } else {
      resident++;
    }
    ct = 0;
  }
  printf("%.1f%% %.1f%%", (float)p_vacant/n*100,(float)vacant/n*100);
  return 0;
}