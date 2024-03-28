class SegTree {
private:
    ll L, R;
    array<SegTree*, 2> kids;
    void recalc();
public:
    ll cache;
    SegTree(ll L, ll R);
    ~SegTree();
    ll range_query(ll l, ll r);
    ll point_query(ll target);
    void point_update(ll target, ll delta);
};
SegTree::SegTree(ll L, ll R) {
    this->L = L;
    this->R = R;
    cache = 0;
    if(L == R)
        kids[0] = kids[1] = nullptr;
    else {
        ll mid = (L + R) >> 1;
        kids[0] = new SegTree(L, mid);
        kids[1] = new SegTree(mid + 1, R);
    }
}
SegTree::~SegTree() {
    delete kids[0];
    delete kids[1];
}
void SegTree::recalc() {
    cache = max(kids[0]->cache, kids[1]->cache);
}
ll SegTree::range_query(ll l, ll r) {
    if(r < L || R < l || r < l)
        return -INF;
    else if(l <= L && R <= r)
        return cache;
    else
        return max(kids[0]->range_query(l, r), kids[1]->range_query(l, r));
}
ll SegTree::point_query(ll target) {
    return range_query(target, target);
}
void SegTree::point_update(ll target, ll delta) {
    if(L == R)
        cache += delta;
    else {
        kids[target > ((L + R) >> 1)]->point_update(target, delta);
        recalc();
    }
}

