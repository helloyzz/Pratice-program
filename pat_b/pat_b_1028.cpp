#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
struct people {
  int year;
  int month;
  int day;
  string name;
};
int main(){
  int n = 0;
  cin >> n;
  string na;
  char bir[11];
  int c = 0;
  people pmin = {-1};
  people pmax = {10000};
  for(int i=0; i<n; i++) {
    cin >> na;
    cin >> bir;
    bir[4] = '\0';
    int year = atoi(bir);
    bir[7] = '\0';
    int month = atoi(bir+5);
    int day = atoi(bir+8);
    if(2014-year>=0 && 2014-year<=200) {
      if(2014-year==200 && 9-month>0) continue;
      if(2014-year==200 && 9-month==0 && 6-day>0) continue;
      if(2014-year==0 && 9-month<0) continue;
      if(2014-year==0 && 9-month==0 && 6-day<0) continue;
      c++;
    } else {
      continue;
    }
    if(year<pmax.year) {
      pmax.year = year;
      pmax.month = month;
      pmax.day = day;
      pmax.name = na;
    } else if(year==pmax.year && month<pmax.month) {
      pmax.year = year;
      pmax.month = month;
      pmax.day = day;
      pmax.name = na;
    } else if(year==pmax.year && month==pmax.month && day<pmax.day) {
      pmax.year = year;
      pmax.month = month;
      pmax.day = day;
      pmax.name = na;
    }
    if(year>pmin.year) {
      pmin.year = year;
      pmin.month = month;
      pmin.day = day;
      pmin.name = na;
    } else if(year==pmin.year && month>pmin.month) {
      pmin.year = year;
      pmin.month = month;
      pmin.day = day;
      pmin.name = na;
    } else if(year==pmin.year && month==pmin.month && day>pmin.day) {
      pmin.year = year;
      pmin.month = month;
      pmin.day = day;
      pmin.name = na;
    }
  }
  cout << c;
  if(c) {
    cout << " " << pmax.name << " " << pmin.name << endl;
  }
  return 0;
}