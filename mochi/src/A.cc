#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,n) for(ll i=0;i<(ll)(n);i++)
#define rep1(i,n) for(ll i=1;i<=(ll)(n);i++)

#define LOCAL 1;
#ifdef LOCAL
#define dbg(x) cerr << __LINE__ << " : " << #x << " = " << (x) << endl
#else
#define dbg(x) true
#endif

template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v) {
  out << "[";
  size_t last = v.size() - 1;
  for (size_t i = 0; i < v.size(); ++i) {
    out << v[i];
    if (i != last)
      out << ", ";
  }
  out << "]";
  return out;
}

template<typename F, typename S>
ostream& operator<< (ostream& out, const pair<F,S>& p) {
  out << "[" << p.first << ", " << p.second << "]";
  return out;
}
ll b;

ll dist (pair<ll,ll> p1, pair<ll,ll> p2){
  return abs(p1.first-p2.first) + abs(p1.second-p2.second);
}

class Car_schedule{
public:
  vector<int> rides;
  ll score=0;
  ll t=0;
  pair<int,int> cor = {0,0};
  Car_schedule(){}

};

class req{
public:
  pair<ll,ll> start_cor,end_cor;
  pair<ll,ll> time_limit;
  int original_idx;
  req(pair<ll,ll> start_cor, pair<ll,ll> end_cor, pair<ll,ll> time_limit, int original_idx) :
  start_cor(start_cor), 
  end_cor(end_cor),
  time_limit(time_limit),
  original_idx(original_idx)
  {

  }
bool operator==(const req& rhs) const
{
  return original_idx == rhs.original_idx;    
}

inline bool operator!=(const req& rhs) const
{
  return !(*this == rhs);
}

bool operator <(const req &rhs) const
{
  return time_limit.first < rhs.time_limit.first;
}

bool operator >(const req &rhs) const
{
  return time_limit.first > rhs.time_limit.first;
}  
};

template<class T>
struct ptr_less
    : public binary_function<T, T, bool> {  
        bool operator()(const T& left, const T& right) const{
            return ((*left) <( *right));
        }
};

bool bonus_check(req request, Car_schedule &car){
  if(car.t + dist(car.cor,request.start_cor) > request.time_limit.first) return false;
  else return true;
}

bool movable_check(req request, Car_schedule &car){
  if(car.t + dist(car.cor,request.start_cor)+dist(request.start_cor, request.end_cor) >= request.time_limit.second) return false;
  else return true;
}

void move_destination(req request, Car_schedule &car){
  car.score += dist(request.start_cor, request.end_cor);
  car.score += ((bonus_check(request,car))?b:0);
  car.rides.push_back(request.original_idx);
  car.t = car.t + dist(car.cor, request.start_cor) + dist(request.start_cor, request.end_cor);
  car.cor = request.end_cor;
}

void make_ans(vector<Car_schedule> Car_schedules){
  ll tot_score = 0;
  rep(i,Car_schedules.size()) tot_score += Car_schedules[i].score;
  rep(i,Car_schedules.size()){
    if(Car_schedules[i].rides.empty()) continue;
    cout << Car_schedules[i].rides.size() <<" ";
    rep(j,Car_schedules[i].rides.size()){
      cout << Car_schedules[i].rides[j] <<" \n"[j==Car_schedules[i].rides.size()-1];
    }
  }
  dbg(tot_score);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll r,c;
  ll f,n,t;
  cin >> r >> c >> f >> n >> b >> t;

  vector<pair<ll,ll>> start,end;
  ll tot_dist = 0;
  vector<pair<ll,ll>> time_limit;

  vector<req> input;

  rep(i,n){
    ll rr1,cc1;
    cin >> rr1 >> cc1;
    ll rr2,cc2;
    cin >> rr2 >> cc2;
    // tot_dist += dist(,end[i]);
    ll st,ed;
    cin >> st >> ed;
    req treq({rr1,cc1},{rr2,cc2},{st,ed},i);
    input.push_back(treq);
  }
  sort(input.begin(),input.end());

  vector<Car_schedule> Car_schedules(f);
  // bonus 狙い
  vector<bool> used(n,false);
  rep(i,n){
    if(used[i]) continue;
    rep(j,f){
      if(bonus_check(input[i],Car_schedules[j])) {
        move_destination(input[i],Car_schedules[j]);
        used[i]=true;
        break;
      }
    }
  }
  // とりあえず移動距離を確保
  rep(i,n){
    if(used[i]) continue;
    rep(j,f){
      if(movable_check(input[i],Car_schedules[j])) {
        move_destination(input[i],Car_schedules[j]);
        used[i]=true;
        break;
      }
    }
  }
  // dbg(used);
  // output
  make_ans(Car_schedules);
  return 0;
}


