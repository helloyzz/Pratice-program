#include <iostream>
using namespace std;
int main() {
  int n = 0;
  char j;
  char y;
  int win[3] = {0};  //获胜次数
  int jia[3] = {0};  //D J C获胜统计
  int yi[3] = {0};   //D J C获胜统计
  cin >> n;
  for(int i=0; i<n; i++) {
    cin >> j;
    cin >> y;
    if(j==y) {
      win[1]++;
    } else if(j=='C' && y=='J') {
      win[0]++;
      jia[0]++;
    } else if(j=='J' && y=='B') {
      win[0]++;
      jia[1]++;
    } else if(j=='B' && y=='C') {
      win[0]++;
      jia[2]++;
    } else if(j=='J' && y=='C') {
      win[2]++;
      yi[0]++;
    } else if(j=='B' && y=='J') {
      win[2]++;
      yi[1]++;
    } else if(j=='C' && y=='B') {
      win[2]++;
      yi[2]++;
    }
  }
  for(int i=0; i<3; i++) {
    cout << win[i];
    if(i!=2) cout << " ";
  }
  cout << endl;
  for(int i=2; i>=0; i--) {
    cout << win[i];
    if(i!=0) cout << " ";
  }
  cout << endl;
  if(jia[2]>=jia[0] && jia[2]>=jia[1]) {
    cout << "B ";
  } else if(jia[0]>=jia[1] && jia[0]>=jia[2]) {
    cout << "C ";
  } else if(jia[1]>=jia[0] && jia[1]>=jia[2]) {
    cout << "J ";
  }
  if(yi[2]>=yi[0] && yi[2]>=yi[1]) {
    cout << "B";
  } else if(yi[0]>=yi[1] && yi[0]>=yi[2]) {
    cout << "C";
  } else if(yi[1]>=yi[0] && yi[1]>=yi[2]) {
    cout << "J";
  }
  return 0;
}