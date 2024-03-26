class FenwickTree {
private:
    vector<ll> T;
    ll query(ll r);
public:
    FenwickTree(ll N);
    ll range_query(ll l, ll r);
    ll point_query(ll target);
    void point_update(ll target, ll delta);
};
FenwickTree::FenwickTree(ll N) {
    T.assign(N + 1, 0);
}
ll FenwickTree::query(ll r) {
    ll result = 0;
    for(ll i = r + 1; i; i -= i & -i)
        result += T[i];
    return result;
}
ll FenwickTree::range_query(ll l, ll r) {
    return query(r) - query(l - 1);
}
ll FenwickTree::point_query(ll target) {
    return query(target) - query(target - 1);
}
void FenwickTree::point_update(ll target, ll delta) {
    for(ll i = target + 1; i < sz(T); i += i & -i)
        T[i] += delta;
}

