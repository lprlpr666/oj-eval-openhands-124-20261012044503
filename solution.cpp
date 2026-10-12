#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SegmentTree {
private:
    int* tree;
    int* lazy;
    int n;
    
    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = 0;
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }
    
    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    
    int query(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (r < start || end < l) {
            return 0;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int left_max = query(2 * node, start, mid, l, r);
        int right_max = query(2 * node + 1, mid + 1, end, l, r);
        return max(left_max, right_max);
    }
    
    void update(int node, int start, int end, int l, int r, int val) {
        push(node, start, end);
        if (r < start || end < l) {
            return;
        }
        if (l <= start && end <= r) {
            lazy[node] += val;
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }
    
public:
    SegmentTree(int size) : n(size) {
        int tree_size = 4 * n + 5;
        tree = new int[tree_size];
        lazy = new int[tree_size];
        for (int i = 0; i < tree_size; i++) {
            tree[i] = lazy[i] = 0;
        }
        build(1, 0, n - 1);
    }
    
    ~SegmentTree() {
        delete[] tree;
        delete[] lazy;
    }
    
    int query_max(int l, int r) {
        if (l > r) return 0;
        return query(1, 0, n - 1, l, r);
    }
    
    void range_add(int l, int r, int val) {
        if (l > r) return;
        update(1, 0, n - 1, l, r, val);
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
    
    SegmentTree st(x - 1);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        if (scanf("%d %d %d", &u, &v, &n) != 3) break;
        
        u--; v--;
        
        if (u >= v) {
            printf("N\n");
            continue;
        }
        
        int max_booked = st.query_max(u, v - 1);
        
        if (max_booked + n <= k) {
            st.range_add(u, v - 1, n);
            printf("T\n");
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}