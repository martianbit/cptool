class SparseTable {
private:
    vector<vector<ll>> T;
    vector<ll> lg;
public:
    SparseTable(const vector<ll> &A);
    ll range_query(ll l, ll r);
};
SparseTable::SparseTable(const vector<ll> &A) {
    lg.resize(sz(A) + 1);
    lg[1] = 0;
    for(ll i = 2; i <= sz(A); i++)
        lg[i] = lg[i >> 1] + 1;
    T.resize(lg.back() + 1);
    T[0].resize(sz(A));
    copy(all(A), T[0].begin());
    for(ll i = 1; i <= lg.back(); i++) {
        T[i].resize(sz(A) - (1LL << i) + 1);
        for(ll j = 0; j < sz(T[i]); j++)
            T[i][j] = max(T[i - 1][j], T[i - 1][j + (1LL << (i - 1))]);
    }
}
ll SparseTable::range_query(ll l, ll r) {
    ll row = lg[r - l + 1];
    return max(T[row][l], T[row][r - (1LL << row) + 1]);
}

