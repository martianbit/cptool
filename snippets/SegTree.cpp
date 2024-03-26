class SegTree {
private:
    bool cached;
    ll L, R;
    array<SegTree*, 2> kids;
public:
    ll cache, lazy;
    SegTree(ll L, ll R);
    ~SegTree();
    ll range_query(ll l, ll r);
    ll point_query(ll target);
    void range_update(ll l, ll r, ll delta);
    void point_update(ll target, ll delta);
};
SegTree::SegTree(ll L, ll R) {
    this->L = L;
    this->R = R;
    cache = lazy = 0;
    cached = true;
    if(L == R)
        fill(all(kids), nullptr);
    else {
        ll mid = (L + R) >> 1;
        kids[0] = new SegTree(L, mid);
        kids[1] = new SegTree(mid + 1, R);
    }
}
SegTree::~SegTree() {
    for(ll i = 0; i < 2; i++)
        delete kids[i];
}
ll SegTree::range_query(ll l, ll r) {
    if(L != R) {
        for(ll i = 0; i < 2; i++)
            kids[i]->lazy += lazy;
    }
    cache += lazy * (R - L + 1);
    lazy = 0;
    if(r < L || R < l || r < l)
        return -INF;
    else if(l <= L && R <= r) {
        if(!cached) {
            cache = max(kids[0]->range_query(L, R), kids[1]->range_query(L, R));
            cached = true;
        }
        return cache;
    }
    else
        return max(kids[0]->range_query(l, r), kids[1]->range_query(l, r));
}
ll SegTree::point_query(ll target) {
    return range_query(target, target);
}
void SegTree::range_update(ll l, ll r, ll delta) {
    if(r < L || R < l || r < l)
        return;
    else if(l <= L && R <= r) {
        cached = L == R;
        lazy += delta;
    }
    else {
        for(ll i = 0; i < 2; i++)
            kids[i]->range_update(l, r, delta);
    }
}
void SegTree::point_update(ll target, ll delta) {
    range_update(target, target, delta);
}

