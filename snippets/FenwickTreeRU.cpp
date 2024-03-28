class FenwickTreeRU {
private:
    array<FenwickTree*, 2> fen;
    ll query(ll r);
public:
    FenwickTreeRU(ll N);
    ~FenwickTreeRU();
    ll range_query(ll l, ll r);
    ll point_query(ll target);
    void range_update(ll l, ll r, ll delta);
    void point_update(ll target, ll delta);
};
FenwickTreeRU::FenwickTreeRU(ll N) {
    fen[0] = new FenwickTree(N);
    fen[1] = new FenwickTree(N);
}
FenwickTreeRU::~FenwickTreeRU() {
    delete fen[0];
    delete fen[1];
}
ll FenwickTreeRU::query(ll r) {
    return fen[0]->range_query(0, r) + fen[1]->range_query(0, r) * (r + 1);
}
ll FenwickTreeRU::range_query(ll l, ll r) {
    return query(r) - query(l - 1);
}
ll FenwickTreeRU::point_query(ll target) {
    return range_query(target, target);
}
void FenwickTreeRU::range_update(ll l, ll r, ll delta) {
    fen[0]->point_update(l, -delta * l);
    fen[0]->point_update(r, +delta * (r + 1));
    fen[1]->point_update(l, +delta);
    fen[1]->point_update(r, -delta);
}
void FenwickTreeRU::point_update(ll target, ll delta) {
    fen[0]->point_update(target, delta);
}

