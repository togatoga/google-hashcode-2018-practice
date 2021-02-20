// -------- START : snippet -------- //

#include <bits/stdc++.h>
using namespace std;

struct IoSetup {
    IoSetup() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
        cerr << fixed << setprecision(10);
    }
} iosetup;

// -------- START : macro -------- //

#define ll long long
#define rep(i,n) for(int i=0;i<int(n);++i)
#define rep1(i,n) for(int i=1;i<=int(n);++i)
#define len(c) (ll)c.size()
#define all(v) (v).begin(),(v).end()
#define lb(v,x) (lower_bound(all(v),x)-v.begin())
#define ub(v,x) (upper_bound(all(v),x)-v.begin())
#define has(c,x) (c.find(x) != c.end())
#define uniq(v) v.erase(unique(all(v)),v.end())
#define bit(k) (1LL<<(k))
#define INF int(1e9)

template<typename T1, typename T2> inline bool chmax(T1 &a, T2 b) { return a < b && (a = b, true); }
template<typename T1, typename T2> inline bool chmin(T1 &a, T2 b) { return a > b && (a = b, true); }

// -------- END : macro -------- //

// -------- START : debug macro -------- //

template<class T,class U> ostream& operator<<(ostream& ost, const pair<T,U> &p) { ost << "(" << p.first << ", " << p.second << ")"; return ost; }
#define ostream_container { ost << "{"; for(const auto &t : v) { if (&t != &*v.begin()) ost << ", "; ost << t; } ost << "}"; return ost; }
template<class T> ostream& operator<<(ostream &ost, const vector<T> &v) ostream_container
template<class T> ostream& operator<<(ostream &ost, const set<T> &v) ostream_container
template<class T,class U> ostream& operator<<(ostream &ost, const map<T,U> &v) ostream_container

template<class H> void recursive_debug(string s, H h) {
    cerr << "\033[33m" << s << " = " << h << endl << "\033[m";
}
template<class H,class... T> void recursive_debug(string s, H h, T... t) {
    int comma = s.find(',');
    cerr << "\033[33m" << s.substr(0,comma) << " = " << h << ", ";
    recursive_debug(s.substr(comma+1), t...);
}
#define debug(...) recursive_debug(#__VA_ARGS__, __VA_ARGS__)

// -------- END : debug macro -------- //

// -------- END : snippet -------- //
struct Ride
{
    int id,sx,sy,gx,gy,s,f,ride_dist;
};



int main(){
    int X, Y, F, N, B, T;
    cin >> X >> Y >> F >> N >> B >> T;
    vector<Ride> r(N);
    rep(i,N) {
        cin >> r[i].sx >> r[i].sy >> r[i].gx >> r[i].gy >> r[i].s >> r[i].f;
        r[i].id = i;
        r[i].ride_dist = abs(r[i].sx - r[i].gx) + abs(r[i].sy - r[i].gy);
    }
    sort(all(r), [](Ride &a, Ride &b){ return a.ride_dist > b.ride_dist; });
    queue<Ride> qu;
    rep(i,N) qu.push(r[i]);
    vector<int> last_t(F), last_x(F), last_y(F);
    vector<vector<int>> res(F);
    while(!qu.empty()) {
        int Q = qu.size();
        Ride cur = qu.front(); qu.pop();
        int choose_i = -1;
        int min_pickup_dist = 20000;
        rep(i,F){
            int pickup_dist = abs(cur.sx - last_x[i]) + abs(cur.sy - last_y[i]);
            if (min_pickup_dist > pickup_dist && last_t[i] + pickup_dist + cur.ride_dist <= cur.f) {
                min_pickup_dist = pickup_dist;
                choose_i = i;
            }
        }
        if (choose_i != -1) {
            res[choose_i].push_back(cur.id);
            int pickup_dist = abs(cur.sx - last_x[choose_i]) + abs(cur.sy - last_y[choose_i]);
            last_t[choose_i] += pickup_dist + cur.ride_dist;
            last_x[choose_i] = cur.gx;
            last_y[choose_i] = cur.gy;
        }
    }

    // output
    rep(i,F) {
        if (res[i].empty()) continue;
        cout << res[i].size() << " ";
        rep(j, res[i].size()) {
            cout << res[i][j] << (j + 1 < (int)res[i].size() ? " " : "\n");
        }
    }
    return 0;
}
