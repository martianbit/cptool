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
void z_algo(const string &s, vector<ll> &z) {
    z.clear();
    z.resize(sz(s));
    z[0] = 0;
    array<ll, 2> z_box = { 0, 0 };
    for(ll i = 1; i < sz(s); i++) {
        ll j = 0;
        if(z_box[0] <= i && i <= z_box[1]) {
            if(i + z[i - z_box[0]] <= z_box[1])
                z[i] = z[i - z_box[0]];
            else
                j = z_box[1] + 1;
        }
        else
            j = i;
        if(j) {
            while(j < sz(s) && s[j] == s[j - i])
                j++;
            z[i] = j - i;
            z_box = { i, j - 1 };
        }
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

