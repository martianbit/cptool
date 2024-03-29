class SegTreeLP {
private:
    ll L, R;
    array<SegTreeLP*, 2> kids;
    void recalc();
    void reset_lazy();
    void handle_lazy();
public:
    ll cache;
    struct {
        bool pending_set;
        ll delta, value;
    } lazy;
    SegTreeLP(ll L, ll R);
    ~SegTreeLP();
    ll range_query(ll l, ll r);
    ll point_query(ll target);
    void range_update(ll l, ll r, ll delta);
    void point_update(ll target, ll delta);
    void range_set(ll l, ll r, ll value);
    void point_set(ll target, ll value);
};
SegTreeLP::SegTreeLP(ll L, ll R) {
    this->L = L;
    this->R = R;
    cache = 0;
    reset_lazy();
    if(L == R)
        kids[0] = kids[1] = nullptr;
    else {
        ll mid = (L + R) >> 1;
        kids[0] = new SegTreeLP(L, mid);
        kids[1] = new SegTreeLP(mid + 1, R);
    }
}
SegTreeLP::~SegTreeLP() {
    delete kids[0];
    delete kids[1];
}
void SegTreeLP::recalc() {
    cache = kids[0]->cache + kids[1]->cache;
}
void SegTreeLP::reset_lazy() {
    lazy = { .pending_set = false, .delta = 0, .value = 0 };
}
void SegTreeLP::handle_lazy() {
    if(lazy.pending_set)
        cache = lazy.value * (R - L + 1);
    cache += lazy.delta * (R - L + 1);
    if(L != R) {
        if(lazy.pending_set)
            kids[0]->lazy = kids[1]->lazy = lazy;
        else {
            kids[0]->lazy.delta += lazy.delta;
            kids[1]->lazy.delta += lazy.delta;
        }
    }
    reset_lazy();
}
ll SegTreeLP::range_query(ll l, ll r) {
    if(r < L || R < l)
        return 0;
    handle_lazy();
    if(l <= L && R <= r)
        return cache;
    else
        return kids[0]->range_query(l, r) + kids[1]->range_query(l, r);
}
ll SegTreeLP::point_query(ll target) {
    return range_query(target, target);
}
void SegTreeLP::range_update(ll l, ll r, ll delta) {
    if(r < L || R < l) {
        handle_lazy();
        return;
    }
    else if(l <= L && R <= r) {
        lazy.delta += delta;
        handle_lazy();
    }
    else {
        handle_lazy();
        kids[0]->range_update(l, r, delta);
        kids[1]->range_update(l, r, delta);
        recalc();
    }
}
void SegTreeLP::point_update(ll target, ll delta) {
    range_update(target, target, delta);
}
void SegTreeLP::range_set(ll l, ll r, ll value) {
    if(r < L || R < l) {
        handle_lazy();
        return;
    }
    else if(l <= L && R <= r) {
        lazy = { .pending_set = true, .delta = 0, .value = value };
        handle_lazy();
    }
    else {
        handle_lazy();
        kids[0]->range_set(l, r, value);
        kids[1]->range_set(l, r, value);
        recalc();
    }
}
void SegTreeLP::point_set(ll target, ll value) {
    range_set(target, target, value);
}

