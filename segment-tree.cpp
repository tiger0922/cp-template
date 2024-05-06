class Segtree {
public:
    vector<int> segtree;
    Segtree(vector<int>& nums) {
        int n = nums.size();
        segtree.resize(4*n);
        build(nums, 0, 0, n-1);
    }

    void build(vector<int>& nums, int v, int tl, int tr) {
        if (tl == tr) {
            segtree[v] = nums[tl];
            return;
        }
        int tmid = (tl+tr)/2;
        build(nums, v*2+1, tl, tmid);
        build(nums, v*2+2, tmid+1, tr);
        segtree[v] = segtree[v*2+1] + segtree[v*2+2];
    }

    void update(int v, int tl, int tr, int pos, int val) {
        if (tl==tr) {
            segtree[v] = val;
            return;
        }
        int tmid = (tl+tr)/2;
        if (pos <= tmid) update(v*2+1,tl,tmid,pos,val);
        else update(v*2+2,tmid+1,tr,pos,val);
        segtree[v] = segtree[v*2+1] + segtree[v*2+2];
    }

    int query(int v, int tl, int tr, int l, int r) {
        if (l>r) return 0;
        if (tl==l && tr==r) {
            return segtree[v];
        }
        int tmid = (tl+tr)/2;
        return query(v*2+1,tl,tmid,l,min(r,tmid)) + 
                query(v*2+2,tmid+1,tr,max(l,tmid+1),r);
    }
};
