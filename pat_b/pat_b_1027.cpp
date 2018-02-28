#include <cstdio>
#include <iostream>

using namespace std;
int num[1004];
int rest[1004];

void preHandle(){
    int sum = 1;
    int cnt = 1;
    for (int i = 1; i < 1004; ++i) {
        if (i >= sum) {
            cnt += 2;
            sum += cnt*2;
        }
        num[i] = cnt - 2;
        rest[i] = i + cnt * 2 - sum;
        
    }
}
int main(){
    
    preHandle();
    
    int n;
    char ch;
    cin >> n >> ch;
    int size = num[n];
    for(int j = 0; j < size;++j){
        for (int i = 0; i < size; ++i) {
            if ((j <= i && j <= size - 1 - i)||(j >= i && j >= size - 1 - i)) {
                cout << ch;
            }else if ((j > i && j < size - 1 - i)) {
                cout << ' ';
            }else{
                break;
            }
        }
        cout << endl;
    }
    
    cout << rest[n] << endl;
    return 0;
}