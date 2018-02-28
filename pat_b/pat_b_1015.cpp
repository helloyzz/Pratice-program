#include <iostream>
using namespace std;
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <new>
struct student{
  int n;
  int m;
  int a;
};
int cmp(const void *a, const void *b) {
  student stu1 = *static_cast<const student*>(a);
  student stu2 = *static_cast<const student*>(b);
  int flag = 0;
  if((stu1.m+stu1.a)>(stu2.m+stu2.a)) {
    flag = 1;
  } else if((stu1.m+stu1.a)==(stu2.m+stu2.a) && (stu1.m>stu2.m)) {
    flag = 1;
  } else if((stu1.m+stu1.a)==(stu2.m+stu2.a) && (stu1.m==stu2.m) && (stu1.n<stu2.n)) {
    flag = 1;
  }
  if(flag) {
    return 1;
  } else{
    return -1;
  }
  return 0;
}

int main() {
  int N = 0;
  int L = 0;
  int H = 0;
  scanf("%d %d %d", &N, &L, &H);
  int n=0;
  int m=0;
  int a=0;
  student* stu_ma_h = new student[N];
  student* stu_m_h = new student[N];
  student* stu_m_g = new student[N];
  student* stu_ma_l = new student[N];
  int s1=0;
  int s2=0;
  int s3=0;
  int s4=0;
  
  for(int i=0; i<N; i++) {
    scanf("%d %d %d", &n, &m, &a);
    if(m>=L && a>=L) {
      if(m>=H && a>=H) {
        stu_ma_h[s1].n = n;
        stu_ma_h[s1].m = m;
        stu_ma_h[s1].a = a;
        s1++;
      } else if(m>=H && a<H) {
        stu_m_h[s2].n = n;
        stu_m_h[s2].m = m;
        stu_m_h[s2].a = a;
        s2++;
      } else if(m<H && a<H && m>=a) {
        stu_m_g[s3].n = n;
        stu_m_g[s3].m = m;
        stu_m_g[s3].a = a;
        s3++;
      } else {
        stu_ma_l[s4].n = n;
        stu_ma_l[s4].m = m;
        stu_ma_l[s4].a = a;
        s4++;
      }
    }
  }
  qsort(stu_ma_h, s1, sizeof(student), cmp);
  qsort(stu_m_h, s2, sizeof(student), cmp);
  qsort(stu_m_g, s3, sizeof(student), cmp);
  qsort(stu_ma_l, s4, sizeof(student), cmp);
  printf("%d\n", (s1+s2+s3+s4));
  for(int i=s1-1; i>=0; i--) {
    printf("%d %d %d\n", stu_ma_h[i].n,stu_ma_h[i].m,stu_ma_h[i].a);
  }
  for(int i=s2-1; i>=0; i--) {
    printf("%d %d %d\n", stu_m_h[i].n,stu_m_h[i].m,stu_m_h[i].a);
  }
  for(int i=s3-1; i>=0; i--) {
    printf("%d %d %d\n", stu_m_g[i].n,stu_m_g[i].m,stu_m_g[i].a);
  }
  for(int i=s4-1; i>=0; i--) {
    printf("%d %d %d\n", stu_ma_l[i].n,stu_ma_l[i].m,stu_ma_l[i].a);
  }
  return 0;
}