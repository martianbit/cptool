vector<ll> _pow;
vector<ll> fact;
void pre_pow(ll a, ll b) {
    _pow.clear();
    _pow.resize(b + 1);
    _pow[0] = 1;
    for(ll i = 1; i <= b; i++)
        _pow[i] = (a * _pow[i - 1]) % MOD;
}
void pre_fact(ll n) {
    fact.clear();
    fact.resize(n + 1);
    fact[0] = 1;
    for(ll i = 1; i <= n; i++)
        fact[i] = (i * fact[i - 1]) % MOD;
}
ll nCr(ll n, ll k) {
    return (fact[n] * inv(fact[k] * fact[n - k])) % MOD;
}

