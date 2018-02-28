#include <stdio.h>
int main() {
  int n = 0;
  scanf("%d", &n);
  int a1 = 0;
  int sum1 = 0;
  int a2 = 0;
  int sum2 = 0;
  int a3 = 0;
  int sum3 = 0;
  int a4 = 0;
  int sum4 = 0;
  int a5 = 0;
  int sum5 = 0;
  int tem = 0;
  for(int i=0; i<n; i++) {
    scanf("%d", &tem);
    if(tem%5==0 && tem%2==0) {
      a1++;
      sum1 += tem;
    } else if(tem%5==1) {
      if(a2%2==0) {
        sum2 += tem;
      } else {
        sum2 -= tem;
      }
      a2++;
    } else if(tem%5==2) {
      a3++;
      sum3++;
    } else if(tem%5==3) {
      a4++;
      sum4 += tem;
    } else if(tem%5==4) {
      a5++;
      if(sum5<tem) {
        sum5 = tem;
      }
    }
  }
  if(a1!=0) {
    printf("%d ", sum1);
  } else {
    printf("N ");
  }
  if(a2!=0) {
    printf("%d ", sum2);
  } else {
    printf("N ");
  }
  if(a3!=0) {
    printf("%d ", sum3);
  } else {
    printf("N ");
  }
  if(a4!=0) {
    printf("%.1lf ", double(sum4)/a4);
  } else {
    printf("N ");
  }
  if(a5!=0) {
    printf("%d", sum5);
  } else {
    printf("N");
  }
  return 0;
} 