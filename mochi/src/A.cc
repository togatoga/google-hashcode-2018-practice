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
  vector<vector<ll>> pizza(m,vector<ll>());
  map<ll,ll> mp_cnt_ing;
  ll ing_idx=0;
  rep(i,m){
    int l;
    cin >> l;
    mp_cnt_ing[l]++;
    set<ll> ss;
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
      pizza[i].push_back(mp[s]);
    }
    assert(ss.size()==l);
  }
  cout <<"ing index & its cnt" << endl;
  for(auto [ing,cnt]:mp_cnt){
    cout << ing <<" "<< cnt << endl;
  }
  cout <<"ing count in a pizza & its cnt" << endl;
  for(auto [ing,cnt]:mp_cnt_ing){
    cout << ing <<" "<< cnt << endl;
  }
  


  return 0;
    

}
