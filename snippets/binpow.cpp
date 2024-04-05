ll binpow(ll a, ll b) {
    a %= MOD;
    ll r = 1;
    while(b) {
        if(b & 1)
            r = (r * a) % MOD;
        b >>= 1;
        a = (a * a) % MOD;
    }
    return r;
}

