ll binpow(ll a, ll b) {
    ll r = 1;
    for(ll i = 62; i >= 0; i--) {
        r = (r * r) % MOD;
        if(b & (1LL << i))
            r = (r * a) % MOD;
    }
    return r;
}

