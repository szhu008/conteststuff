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

#define MAXN 200005
#define MOD 1000000007
#define INF 10e16

struct line{
    ll m;
    ll b;
    bool operator<(const line &l) const{
        return this->m == l.m ? this->b >l.b : this->m < l.m;
    }
    bool operator==(const line &l){
        return this-> m == l.m && this->b == l.b;
    }
};

double intersect(line a, line b){
    if (a.b == b.b) return a.b;
    return double(a.b - b.b)/double(b.m - a.m);
}

line l[MAXN];

vector<line> hull;
vector<double> seg;
ll a[MAXN], sum[MAXN];
ll n;
void buildHull(){
    sort(l, l+n);
    hull.clear();
    seg.clear();
    for (int i = 0; i < n; i++){
        if (i && l[i] == l[i-1]) continue;
        while (hull.size() > 1 &&
               intersect(l[i], hull.back()) <= intersect(hull.back(), hull[hull.size()-2] )){
            hull.pop_back();
            seg.pop_back();
        }
        if (hull.size() >= 1){
            seg.push_back(intersect(hull.back(), l[i]));
        }
        hull.push_back(l[i]);
    }
    seg.push_back(INF);
}

int main() {
    memset(sum, 0, sizeof(sum));
    cin >> n;
    ll ores = 0;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        if (i)
            sum[i] = sum[i-1] + a[i];
        else
            sum[i] = a[i];
        ores += (i+1)*a[i];
    }
    
    ll res = 0;
    //left shifts
    for (int i = 1; i <= n; i++){
        l[i-1] = line{i, -sum[i-1]};
    }
    buildHull();
    for (int i = 0; i < n; i++){
        int it = lower_bound(seg.begin(), seg.end(), a[i])  - seg.begin();
        ll val = a[i] * hull[it].m + hull[it].b - a[i]*(i+1) + sum[i];
        res = max(res, val);
    }
    //right shifts
    for (int i = 1; i <= n; i++){
        if (i == 1){
            l[i-1] = line{i, 0};
        }
        else {
            l[i-1] = line{i, -sum[i-2]};
        }
    }
    buildHull();
    for (int i = 0; i < n; i++){
        int it = lower_bound(seg.begin(), seg.end(), a[i])  - seg.begin();
        ll val = a[i] * hull[it].m + hull[it].b - a[i]*(i+1) + sum[i-1];
        res = max(res, val);
    }
    cout << ores+res << endl;
    return 0;
}
