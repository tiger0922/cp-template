using LL = long long;

class Segtree {
    vector<LL> segtree;
    vector<LL> lazy;
public:
    Segtree(vector<LL>& arr) {
        int n = arr.size();
        segtree = vector<LL>(4*n);
        lazy = vector<LL>(4*n, 0);
        build(arr, 0, 0, n-1); 
    } 
    void build(vector<LL>& arr, int pos, int tl, int tr) {
        if (tl == tr) {
            segtree[pos] = arr[tl];
        } else {
            int tm = (tl+tr)/2;
            build(arr, pos*2+1, tl, tm);
            build(arr, pos*2+2, tm+1, tr);
            segtree[pos] = max(segtree[pos*2+1], segtree[pos*2+2]);
        }
    }
    void push(int pos) {
        segtree[pos*2+1] += lazy[pos];
        lazy[pos*2+1] += lazy[pos];
        segtree[pos*2+2] += lazy[pos];
        lazy[pos*2+2] += lazy[pos];
        lazy[pos] = 0;
    }
    void update(int pos, int tl, int tr, int l, int r, LL addend) {
        if (l > r) 
            return;
        if (l == tl && r == tr) {
            segtree[pos] += addend;
            lazy[pos] += addend;
        } else {
            push(pos);
            int tm = (tl + tr) / 2;
            update(pos*2+1, tl, tm, l, min(r, tm), addend);
            update(pos*2+2, tm+1, tr, max(l, tm+1), r, addend);
            segtree[pos] = max(segtree[pos*2+1], segtree[pos*2+2]);
        }
    }
    LL query(int pos, int tl, int tr, int l, int r) {
        if (l > r)
            return LLONG_MIN;
        if (l == tl && tr == r)
            return segtree[pos];
        push(pos);
        int tm = (tl + tr) / 2;
        return max(query(pos*2+1, tl, tm, l, min(r, tm)), 
                   query(pos*2+2, tm+1, tr, max(l, tm+1), r));
    }
};

