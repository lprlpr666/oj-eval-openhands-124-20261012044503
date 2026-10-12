#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x, k, p;
    if (!(cin >> x >> k >> p)) return 0;
    
    vector<int> seats(x, 0);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        if (!(cin >> u >> v >> n)) break;
        
        u--; v--;
        
        bool can_fulfill = true;
        for (int j = u; j < v; j++) {
            if (seats[j] + n > k) {
                can_fulfill = false;
                break;
            }
        }
        
        if (can_fulfill) {
            for (int j = u; j < v; j++) {
                seats[j] += n;
            }
            cout << "T\n";
        } else {
            cout << "N\n";
        }
    }
    
    return 0;
}