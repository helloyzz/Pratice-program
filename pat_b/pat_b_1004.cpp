#include <iostream>
using namespace std;
#include <map>
#include <utility>

int main(int argc, char** argv) {
  string num;
  getline(cin, num);
  int n = atoi(num.c_str());
  string str[n];
  map<int,int> stu_score;
  for(int i=0; i<n; i++) {
    getline(cin, str[i]);
    int p = str[i].rfind(' ');
    string sub = str[i].substr(p+1);
    int score = atoi(sub.c_str());
    stu_score.insert(stu_score.begin(), pair<int, int>(i, score));
  }
  int min = 0xffff;
  int max = 0;
  int px = 0;
  int pn = 0;
  map<int, int>::iterator iter = stu_score.begin();
  for(int i=0; i<n; i++) {
    int tem = iter->second;  
    if(max<tem) {
      max = tem;
      px = iter->first;
    }
    if(min>tem) {
      min = tem;
      pn = iter->first;
    }
    iter++;
  }
  int p1 = str[px].rfind(' ');
  int p2 = str[pn].rfind(' ');
  cout << str[px].substr(0, p1) << endl;
  cout << str[pn].substr(0, p2) << endl;
  
  return 0;
}