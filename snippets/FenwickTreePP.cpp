class FenwickTreePP {
private:
    array<FenwickTree*, 2> fen;
    ll query(ll r);
public:
    FenwickTreePP(ll N);
    ~FenwickTreePP();
    ll range_query(ll l, ll r);
    ll point_query(ll target);
    void range_update(ll l, ll r, ll delta);
    void point_update(ll target, ll delta);
};
FenwickTreePP::FenwickTreePP(ll N) {
    for(ll i = 0; i < 2; i++)
        fen[i] = new FenwickTree(N);
}
FenwickTreePP::~FenwickTreePP() {
    for(ll i = 0; i < 2; i++)
        delete fen[i];
}
ll FenwickTreePP::query(ll r) {
    return fen[0]->range_query(0, r) + fen[1]->range_query(0, r) * (r + 1);
}
ll FenwickTreePP::range_query(ll l, ll r) {
    return query(r) - query(l - 1);
}
ll FenwickTreePP::point_query(ll target) {
    return query(target) - query(target - 1);
}
void FenwickTreePP::range_update(ll l, ll r, ll delta) {
    fen[0]->point_update(l, -delta * l);
    fen[0]->point_update(r, +delta * (r + 1));
    fen[1]->point_update(l, +delta);
    fen[1]->point_update(r, -delta);
}
void FenwickTreePP::point_update(ll target, ll delta) {
    fen[0]->point_update(target, delta);
}

