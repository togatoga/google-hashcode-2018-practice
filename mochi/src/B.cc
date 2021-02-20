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

class ans{
public:
  vector<vector<ll>> two;
  vector<vector<ll>> three;
  vector<vector<ll>> four;
};

class team_state{
public:
  int sz;
  set<int> ing_set;
  vector<int> ans;
  int remain;
  team_state(int sz) : sz(sz){
    remain = sz;
  }
};

void fill(int team_num, vector<team_state> &num, vector<bool> &used, vector<pair<int,vector<ll>>> pizza, bool anything){
  rep(i,pizza.size()){
    if(used[i]) continue;
    rep(j,team_num){
      if(num[j].remain>0){
        bool ok = false;
        if(anything) ok=true;
        else{
          rep(l,pizza[i].second.size()){
            if(num[j].ing_set.count(pizza[i].second[l])==0) ok = true;
          }
        }
        if(ok){
          used[i]=true;
          num[j].remain--;
          rep(l,pizza[i].second.size()){
            num[j].ing_set.insert(pizza[i].second[l]);
          }
          num[j].ans.push_back(pizza[i].first);
          break;
        }
      }
    }
  }
}
int pt=0;
int make_ans(vector<team_state> &num, int team_sz, bool cnt){
  int res=0;
  rep(i,num.size()){
    if(num[i].remain==0){
      if(!cnt) cout << team_sz << " ";
      res++;
      rep(j,num[i].ans.size()){
        if(!cnt) cout << num[i].ans[j] <<" \n"[j==num[i].ans.size()-1];
        // if(!cnt) cout << num[i].ans[j] <<" ";
      }
      // if(!cnt) {
      //   cout << num[i].ing_set.size() << endl;
        pt += num[i].ing_set.size() * num[i].ing_set.size();
      // }
    }
  }
  return res;
}
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll m;
  vector<ll> team(3);
  cin  >> m;
  rep(i,3) cin >> team[i];
  map<string,ll> mp;
  map<ll,string> mp_inv;
  map<ll,ll> mp_cnt;
  vector<pair<int,vector<ll>>> pizza(m,pair<int,vector<ll>>());
  map<ll,ll> mp_cnt_ing;
  ll ing_idx=0;
  rep(i,m){
    int l;
    cin >> l;
    mp_cnt_ing[l]++;
    set<ll> ss;
    vector<ll> tmp;
    rep(j,l){
      string s;
      cin >> s;
      if(!mp.count(s)){
        mp[s]=ing_idx;
        mp_inv[ing_idx]=s;
        ing_idx++;
      }
      ss.insert(mp[s]);
      mp_cnt[mp[s]]++;
      tmp.push_back(mp[s]);
    }
    pizza[i] = {i,tmp};
    assert(ss.size()==l);
  }
  vector<team_state> two(team[0],team_state(2));
  vector<team_state> three(team[1],team_state(3));
  vector<team_state> four(team[2],team_state(4));

  vector<bool> used(m,false);
  sort(pizza.begin(),pizza.end(),[](pair<int,vector<ll>> const& lhs, pair<int,vector<ll>> const& rhs){
    return lhs.second.size() > rhs.second.size();
  });
  fill(team[2],four,used,pizza,false);
  fill(team[1],three,used,pizza,false);
  fill(team[0],two,used,pizza,false);
  fill(team[2],four,used,pizza,true);
  fill(team[1],three,used,pizza,true);
  fill(team[0],two,used,pizza,true);
  ll ans_num=0;
  // ans_num += make_ans(two,2,true);
  // ans_num += make_ans(three,3,true);
  // ans_num += make_ans(four,4,true);
  // cout << ans_num << endl;

  make_ans(two,2,false);
  make_ans(three,3,false);
  make_ans(four,4,false);

  cout << pt << endl;
  return 0;
    

}