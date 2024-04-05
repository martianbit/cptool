void hash_str(const string &s, vector<ll> &result) {
    result.clear();
    result.resize(sz(s));
    result[0] = s[0];
    ll p = 1;
    for(ll i = 1; i < sz(s); i++) {
        p = (p * HASHP) % MOD;
        result[i] = (((s[i] * p) % MOD) + result[i - 1]) % MOD;
    }
}
void compute_lps(const string &s, vector<ll> &lps) {
    lps.clear();
    lps.resize(sz(s));
    lps[0] = 0;
    ll i = 1;
    ll j = 0;
    while(i < sz(s)) {
        if(s[i] == s[j])
            lps[i++] = ++j;
        else if(j)
            j = lps[j - 1];
        else
            i++;
    }
}
void KMP(const string &s, const string &p, vector<ll> &result) {
    result.clear();
    vector<ll> lps; compute_lps(p, lps);
    ll i, j;
    i = j = 0;
    while(i < sz(s)) {
        if(s[i] == p[j]) {
            if(++j == sz(p)) {
                result.push_back(i);
                j = lps.back();
            }
            i++;
        }
        else if(j)
            j = lps[j - 1];
        else
            i++;
    }
}

