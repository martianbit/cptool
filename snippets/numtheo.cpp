void find_divisors(ll n, vector<ll> &divs) {
    divs.clear();
    ll i;
    for(i = 1; i * i < n; i++) {
        if(n % i)
            continue;
        divs.push_back(i);
        divs.push_back(n / i);
    }
    if(i * i == n)
        divs.push_back(i);
}
ll extended_euclidean(ll a, ll m) {
    if(!a)
        return -1;
    if(m == 1)
        return 0;
    if(a == 1)
        return 1;
    ll x, y, z, s, inv;
    stack<ll> st;
    x = m;
    y = mod(a, m);
    while(true) {
        st.push(x / y);
        z = y;
        y = x % y;
        x = z;
        if(!y)
            return -1;
        if(y == 1)
            break;
    }
    s = sz(st);
    x = 0;
    y = 1;
    while(!st.empty()) {
        z = x;
        x = y;
        y = z + x * st.top();
        st.pop();
    }
    inv = y * ((s & 1) ? -1 : 1) * ((a < 0) ? -1 : 1);
    inv = mod(inv, m);
    return inv;
}

