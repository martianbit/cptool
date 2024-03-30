class DSU {
private:
    vector<ll> P, rank;
public:
    DSU(ll N);
    void make_set(ll v);
    ll find_set(ll v);
    void union_sets(ll a, ll b);
};
DSU::DSU(ll N) {
    P.resize(N);
    rank.resize(N);
}
void DSU::make_set(ll v) {
    P[v] = v;
    rank[v] = 0;
}
ll DSU::find_set(ll v) {
    if(P[v] != v)
        P[v] = find_set(P[v]);
    return P[v];
}
void DSU::union_sets(ll a, ll b) {
    a = find_set(a);
    b = find_set(b);
    if(a == b)
        return;
    if(rank[a] < rank[b])
        swap(a, b);
    P[b] = a;
    rank[a] += rank[a] == rank[b];
}

