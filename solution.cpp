#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX_N = 4000005;

int tree[MAX_N];
int lazy[MAX_N];

void push(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += lazy[node];
        if (start != end) {
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = 0;
    } else {
        int mid = (start + end) / 2;
        build(2*node, start, mid);
        build(2*node+1, mid+1, end);
        tree[node] = max(tree[2*node], tree[2*node+1]);
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
    int left = query(2*node, start, mid, l, r);
    int right = query(2*node+1, mid+1, end, l, r);
    return max(left, right);
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
    update(2*node, start, mid, l, r, val);
    update(2*node+1, mid+1, end, l, r, val);
    tree[node] = max(tree[2*node], tree[2*node+1]);
}

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
    
    build(1, 0, x-2);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        if (scanf("%d %d %d", &u, &v, &n) != 3) break;
        
        u--; v--;
        
        if (u >= v) {
            printf("N\n");
            continue;
        }
        
        int max_booked = query(1, 0, x-2, u, v-1);
        
        if (max_booked + n <= k) {
            update(1, 0, x-2, u, v-1, n);
            printf("T\n");
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}