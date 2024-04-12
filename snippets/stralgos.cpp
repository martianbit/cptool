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
void aho_corasick(const string &s, const vector<string> &p, vector<ll> &result) {
    result.clear();
    result.assign(sz(p), 0);
    typedef struct {
        ll cnt, fail;
        vector<ll> dict;
        array<ll, 26> edges;
    } TrieVertex;
    vector<TrieVertex> trie;
    trie.emplace_back();
    trie.push_back({ .fail = 1 });
    for(ll i = 0; i < sz(p); i++) {
        ll v = 1;
        for(const auto &x : p[i]) {
            if(!trie[v].edges[x - 'a']) {
                trie[v].edges[x - 'a'] = sz(trie);
                trie.emplace_back();
            }
            v = trie[v].edges[x - 'a'];
        }
        trie[v].dict.push_back(i);
    }
    queue<ll> q;
    for(ll i = 0; i < 26; i++) {
        if(trie[1].edges[i]) {
            trie[trie[1].edges[i]].fail = 1;
            q.push(trie[1].edges[i]);
        }
        else
            trie[1].edges[i] = 1;
    }
    while(!q.empty()) {
        auto v = q.front();
        q.pop();
        for(ll i = 0; i < 26; i++) {
            if(trie[v].edges[i]) {
                trie[trie[v].edges[i]].fail = trie[trie[v].fail].edges[i];
                q.push(trie[v].edges[i]);
            }
            else
                trie[v].edges[i] = trie[trie[v].fail].edges[i];
        }
    }
    vector<vector<ll>> AL(sz(trie));
    for(ll i = 2; i < sz(trie); i++)
        AL[trie[i].fail].push_back(i);
    ll state = 1;
    for(const auto &x : s) {
        state = trie[state].edges[x - 'a'];
        trie[state].cnt++;
    }
    function<void(ll)> dfs = [&](ll v) -> void {
        for(const auto &x : AL[v]) {
            dfs(x);
            trie[v].cnt += trie[x].cnt;
        }
        for(const auto &x : trie[v].dict)
            result[x] = trie[v].cnt;
    };
    dfs(1);
}

