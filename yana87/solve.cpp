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

struct Ride {
    int id,sx,sy,gx,gy,s,f,ride_dist;
    bool done;
    vector<int> candidate;
};
struct Vehicle {
    int id,x,y,t,best_ride_id,best_empty_time;
    double best_benefit;
};

int main(){
    int X, Y, F, N, B, T;
    cin >> X >> Y >> F >> N >> B >> T;
    vector<Ride> r(N);
    rep(i,N) {
        cin >> r[i].sx >> r[i].sy >> r[i].gx >> r[i].gy >> r[i].s >> r[i].f;
        r[i].id = i;
        r[i].ride_dist = abs(r[i].sx - r[i].gx) + abs(r[i].sy - r[i].gy);
        r[i].done = false;
    }

    using P = pair<double,int>; // benefit, Vehicle.id
    priority_queue<P> qu;
    vector<Vehicle> v(F);
    vector<vector<int>> res(F);

    auto calc_empty_time = [&](int vcl_id, int ride_id) {
        if (vcl_id == -1 || ride_id == -1) return INF;
        return max(abs(r[ride_id].sx - v[vcl_id].x) + abs(r[ride_id].sy - v[vcl_id].y), r[ride_id].s - v[vcl_id].t);
    };

    // tuning
    auto calc_benefit = [&](Vehicle &vcl, Ride &ride) {
        int empty_time = calc_empty_time(vcl.id, ride.id);
        return - (double) empty_time + (ride.ride_dist > 4000 ? ride.ride_dist/10.0 : 0.0);
    };

    auto set_near = [&](Vehicle &vcl) {
        vcl.best_ride_id = -1;
        vcl.best_empty_time = INF;
        vcl.best_benefit = -INF;
        rep(i,N){
            if (r[i].done) continue;
            int empty_time = calc_empty_time(vcl.id, i);
            if (vcl.t + empty_time + r[i].ride_dist > r[i].f) continue;
            auto benefit = calc_benefit(vcl, r[i]);
            if (vcl.best_benefit < benefit) {
                vcl.best_ride_id = i;
                vcl.best_empty_time = empty_time;
                vcl.best_benefit = benefit;
            }
        }
        if (vcl.best_ride_id != -1) {
            r[vcl.best_ride_id].candidate.push_back(vcl.id);
            qu.push({vcl.best_benefit, vcl.id});
        }
    };

    rep(i,F) {
        v[i].id = i;
        v[i].x = v[i].y = v[i].t = 0;
        set_near(v[i]);
    }
    while(!qu.empty()) {
        Vehicle &vcl = v[qu.top().second];
        double old_benefit = qu.top().first;
        qu.pop();
        if (abs(vcl.best_benefit - old_benefit) > 1e-3) continue; 
        if (vcl.best_ride_id == -1) continue;
        Ride &ride = r[vcl.best_ride_id];
        if (ride.done) continue;
        vcl.x = ride.gx;
        vcl.y = ride.gy;
        vcl.t += vcl.best_empty_time + ride.ride_dist;
        ride.done = true;
        for (int vcl_id : ride.candidate) {
            set_near(v[vcl_id]);
        }
        set_near(vcl);
        res[vcl.id].push_back(ride.id);
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
