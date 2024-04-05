ll inv(ll a);
ll binpow(ll a, ll b) {
    if(b < 0)
        return inv(binpow(a, -b));
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
ll inv(ll a) {
    return binpow(a, MOD - 2);
}
