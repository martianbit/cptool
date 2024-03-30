class FenwickTree2D {
private:
    vector<vector<ll>> T;
    ll query(ll x, ll y);
public:
    FenwickTree2D(ll N);
    ll range_query(ll x1, ll y1, ll x2, ll y2);
    void point_update(ll x, ll y, ll delta);
};
FenwickTree2D::FenwickTree2D(ll N) {
    T.assign(N + 1, vector<ll>(N + 1, 0));
}
ll FenwickTree2D::query(ll x, ll y) {
    ll result = 0;
    for(ll i = y + 1; i; i -= i & -i) {
        for(ll j = x + 1; j; j -= j & -j)
            result += T[i][j];
    }
    return result;
}
ll FenwickTree2D::range_query(ll x1, ll y1, ll x2, ll y2) {
    return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
}
void FenwickTree2D::point_update(ll x, ll y, ll delta) {
    for(ll i = y + 1; i < sz(T); i += i & -i) {
        for(ll j = x + 1; j < sz(T[i]); j += j & -j)
            T[i][j] += delta;
    }
}

