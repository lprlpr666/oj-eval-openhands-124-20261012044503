#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int BLOCK_SIZE = 1000;

class BlockArray {
private:
    vector<int> data;
    vector<int> block_max;
    int n;
    int block_cnt;
    
    int get_block(int idx) {
        return idx / BLOCK_SIZE;
    }
    
    void update_block_max(int block_id) {
        int start = block_id * BLOCK_SIZE;
        int end = min(start + BLOCK_SIZE, n);
        block_max[block_id] = 0;
        for (int i = start; i < end; i++) {
            block_max[block_id] = max(block_max[block_id], data[i]);
        }
    }
    
public:
    BlockArray(int size) : n(size) {
        data.resize(n, 0);
        block_cnt = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;
        block_max.resize(block_cnt, 0);
    }
    
    int query_max(int l, int r) {
        if (l > r) return 0;
        int result = 0;
        
        int left_block = get_block(l);
        int right_block = get_block(r);
        
        if (left_block == right_block) {
            for (int i = l; i <= r; i++) {
                result = max(result, data[i]);
            }
        } else {
            for (int i = l; i < (left_block + 1) * BLOCK_SIZE && i < n; i++) {
                result = max(result, data[i]);
            }
            for (int block = left_block + 1; block < right_block; block++) {
                result = max(result, block_max[block]);
            }
            for (int i = right_block * BLOCK_SIZE; i <= r; i++) {
                result = max(result, data[i]);
            }
        }
        
        return result;
    }
    
    void range_add(int l, int r, int val) {
        if (l > r) return;
        
        int left_block = get_block(l);
        int right_block = get_block(r);
        
        if (left_block == right_block) {
            for (int i = l; i <= r; i++) {
                data[i] += val;
            }
            update_block_max(left_block);
        } else {
            for (int i = l; i < (left_block + 1) * BLOCK_SIZE && i < n; i++) {
                data[i] += val;
            }
            update_block_max(left_block);
            
            for (int block = left_block + 1; block < right_block; block++) {
                for (int i = block * BLOCK_SIZE; i < (block + 1) * BLOCK_SIZE && i < n; i++) {
                    data[i] += val;
                }
                update_block_max(block);
            }
            
            for (int i = right_block * BLOCK_SIZE; i <= r; i++) {
                data[i] += val;
            }
            update_block_max(right_block);
        }
    }
};

int main() {
    int x, k, p;
    if (scanf("%d %d %d", &x, &k, &p) != 3) return 0;
    
    if (x <= 1) {
        for (int i = 0; i < p; i++) {
            int u, v, n;
            if (scanf("%d %d %d", &u, &v, &n) != 3) break;
            printf("N\n");
        }
        return 0;
    }
    
    BlockArray ba(x - 1);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        if (scanf("%d %d %d", &u, &v, &n) != 3) break;
        
        u--; v--;
        
        if (u >= v) {
            printf("N\n");
            continue;
        }
        
        int max_booked = ba.query_max(u, v - 1);
        
        if (max_booked + n <= k) {
            ba.range_add(u, v - 1, n);
            printf("T\n");
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}