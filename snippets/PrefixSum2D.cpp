class PrefixSum2D {
private:
    vector<vector<ll>> cum;
public:
    PrefixSum2D(const vector<vector<ll>> &A);
    ll query(ll x1, ll y1, ll x2, ll y2);
};
PrefixSum2D::PrefixSum2D(const vector<vector<ll>> &A) {
    cum.assign(sz(A), vector<ll>(sz(A[0])));
    for(ll i = 0; i < sz(A); i++) {
        for(ll j = 0; j < sz(A[0]); j++)
            cum[i][j] = A[i][j] + (i ? cum[i - 1][j] : 0) + (j ? cum[i][j - 1] : 0) - ((i && j) ? cum[i - 1][j - 1] : 0);
    }
}
ll PrefixSum2D::query(ll x1, ll y1, ll x2, ll y2) {
    return cum[y2][x2] - (x1 ? cum[y2][x1 - 1] : 0) - (y1 ? cum[y1 - 1][x2] : 0) + ((x1 && y1) ? cum[y1 - 1][x1 - 1] : 0);
}

