//
//  main.cpp
//  facebookhackercup
//
//  Created by Stephen Zhu on 1/8/16.
//  Copyright (c) 2016 Stephen Zhu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <map>
#include <deque>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <set>
#include <random>
#include <float.h>
#include <cassert>
#include <cstdlib>
#include <limits>
using namespace std;

typedef long long ll;

#define MAXN 400005
#define MOD 1000000007

ll segs[] = {6,2,5,5,4,5,6,3,7,6};

ll t[4*MAXN], lazy[4*MAXN];

ll n, m;

void push(ll ind){
    if (lazy[ind] == -1) return;
    lazy[ind*2+1] = t[ind*2+1] = lazy[ind];
    lazy[ind*2+2] = t[ind*2+2] = lazy[ind];
    lazy[ind] = -1;
    return;
}


void upd(ll ind, ll l, ll r, ll curL, ll curR, ll val){
    if (curL > curR) return;
    if (l == curL && r == curR){
        lazy[ind] = 1LL << val;
        t[ind] = 1LL << val;
    }
    else {
        push(ind);
        ll mid = (l + r)/2;
        upd(ind*2+1, l, mid, curL, min(curR, mid), val);
        upd(ind*2+2, mid+1, r, max(curL, mid+1), curR, val);
        t[ind] = t[ind*2+1] | t[ind*2 + 2];
    }
}

ll gt(ll ind, ll l, ll r, ll curL, ll curR){
    ll res = 0;
    if (curL > curR)
        return 0;
    if (l == curL && r == curR){
        return t[ind];
    } else{
        push(ind);
        ll mid = (l+r)/2;
        ll left = gt(ind*2+1, l, mid, curL, min(curR, mid));
        ll right = gt(ind*2+2, mid+1, r, max(curL, mid+1), curR);
        res = left | right;
    }
    return res;
}

vector<int> edge[MAXN];

ll val[MAXN];
pair<ll, ll> seg[MAXN];
bool seen[MAXN];
vector<ll> newVal;
void dfs(int ind){
    seen[ind] = true;
    newVal.push_back(ind);
    seg[ind].first = newVal.size()-1;
    for (int i = 0; i < edge[ind].size(); i++){
        if (!seen[edge[ind][i]])
            dfs(edge[ind][i]);
    }
    seg[ind].second = newVal.size() -1;
}

int countOnes(ll ind){
    int res = 0;
    while (ind){
        if (ind & 1)
            res++;
        ind /= 2;
    }
    return res;
}

int main() {
    memset(t, 0, sizeof(t));
    memset(lazy, -1, sizeof(lazy));
    memset(seen, false, sizeof(seen));
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        cin >> val[i];
    }
    for (int i = 0; i < n-1; i++){
        ll to, from;
        cin >> to >> from;
        edge[to-1].push_back(from-1);
        edge[from-1].push_back(to-1);
    }
    dfs(0);
    for (int i = 0; i < n; i++){
        upd(0, 0, n-1, i, i, val[newVal[i]]);
    }

    for (int i = 0; i < m; i++){
        int tp;
        cin >> tp;
        if (tp == 1){
            ll node, v;
            cin >> node >> v;
            upd(0, 0, n-1, seg[node-1].first, seg[node-1].second, v);
        }
        else {
            ll node;
            cin >> node;
            ll res = gt(0, 0, n-1, seg[node-1].first, seg[node-1].second);
            cout << countOnes(res) << endl;
        }

    }


    return 0;
}
