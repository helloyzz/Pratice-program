#include <cstdlib>
#include <cstdio>
using namespace std;
struct yueb {
  int type;
  float weight;
  float val;
  float price;
};
int cmp2(const void* a, const void* b) {
  yueb arg1 = *static_cast<const yueb*>(a);
  yueb arg2 = *static_cast<const yueb*>(b);
  if(arg1.val>arg2.val) {
    return -1;
  } else {
    return 1;
  }
  return 0;
}

int main(){
  int t = 0;
  int r = 0;
  scanf("%d %d", &t, &r);
  float w;
  float p;
  yueb yb[1001];
  for(int i=0; i<t; i++) {
    scanf("%f",&w);
    yb[i].type = i;
    yb[i].weight = w;
  }
  for(int i=0; i<t; i++) {
    scanf("%f",&p);
    yb[i].price = p;
  }
  for(int i=0; i<t; i++) {
    yb[i].val = yb[i].price/yb[i].weight;
  }
  qsort(yb, t, sizeof(yueb), &cmp2);
  float sum = 0;
  float res = 0;
  float m = 0;
  for(int i=0; i<t; i++) {
    sum += yb[i].weight;
    if(sum>=r) {
      m = sum-r;
      res += yb[i].val*(yb[i].weight-m);
      break;
    }
    res += yb[i].price;
  }
  printf("%.2f", res);
  return 0;
}