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
  vector<set<team_state> > nokori(3,set<team_state>());
  rep(i,num.size()){
    if(num[i].remain==0){
      if(!cnt) cout << team_sz << " ";
      res++;
      rep(j,num[i].ans.size()){
        if(!cnt) cout << num[i].ans[j] <<" \n"[j==num[i].ans.size()-1];
        // if(!cnt) cout << num[i].ans[j] <<" ";
      }
        pt += num[i].ing_set.size() * num[i].ing_set.size();
    }
    else{
      if(!nokori[4-num[i].remain].empty()){
        num[i].ans.push_back()
      }
      cerr << num[i].remain << endl;
    }
  }
  return res;
}

void swap_array_and_update(team_state &s1, int fidx, team_state &s2, int sidx, vector<vector<ll>> &original_pizza){
    // int tmp = s1.ans[fidx];
    // s1.ans[fidx] = s2.ans[sidx];
    // s2.ans[sidx] = tmp;
    int pscore = s1.ing_set.size()*s1.ing_set.size() + s2.ing_set.size()*s2.ing_set.size();
    set<int> n1_ing_set;
    set<int> n2_ing_set;
    rep(i,s1.ans.size()){
      if(i==fidx){
        rep(j,original_pizza[s1.ans[i]].size()){
          n2_ing_set.insert(original_pizza[s1.ans[i]][j]);
        }
      }
      else{
        rep(j,original_pizza[s1.ans[i]].size()){
          n1_ing_set.insert(original_pizza[s1.ans[i]][j]);
        }        
      }
    }
    rep(i,s2.ans.size()){
      if(i==sidx){
        rep(j,original_pizza[s2.ans[i]].size()){
          n1_ing_set.insert(original_pizza[s2.ans[i]][j]);
        }
      }
      else{
        rep(j,original_pizza[s2.ans[i]].size()){
          n2_ing_set.insert(original_pizza[s2.ans[i]][j]);
        }        
      }
    }
    int nscore = n1_ing_set.size()*n1_ing_set.size() + n2_ing_set.size() *n2_ing_set.size();
    // cerr << nscore <<" " << pscore << endl;
    if(nscore > pscore) {
      s1.ing_set = n1_ing_set;
      s2.ing_set = n2_ing_set;
      swap(s1.ans[fidx],s2.ans[sidx]);
    }
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
  vector<vector<ll>> original_pizza(m,vector<ll>());


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
    original_pizza[i] = tmp;
    assert(ss.size()==l);
  }
  vector<vector<team_state>> num(3,vector<team_state>());
  rep(i,3){
    num[i]= vector<team_state>(team[i],team_state(2+i));
  }
  vector<bool> used(m,false);
  sort(pizza.begin(),pizza.end(),[](pair<int,vector<ll>> const& lhs, pair<int,vector<ll>> const& rhs){
    return lhs.second.size() > rhs.second.size();
  });
  for(int i=2;i>=0;i--){
  // rep(i,3){
    fill(team[i],num[i],used,pizza,false);
  }
  for(int i=2;i>=0;i--){
  // rep(i,3){
    fill(team[i],num[i],used,pizza,true);
  }

  ll kai = 1e5;
  // rep(i,kai){
  //   mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
  //   uniform_int_distribution<int> dist_n(0, 2);
  //   int fn = dist_n(rng);
  //   int sn = dist_n(rng);
  //   int lf = num[fn].size()-1;
  //   int ls = num[sn].size()-1;
  //   uniform_int_distribution<int> dist_lf(0, lf);
  //   uniform_int_distribution<int> dist_ls(0, ls);

  //   int team_idxf = dist_lf(rng);
  //   int team_idxs = dist_ls(rng);

  //   uniform_int_distribution<int> dist_lf2(0, num[fn][team_idxf].ans.size()-1);
  //   uniform_int_distribution<int> dist_ls2(0, num[sn][team_idxs].ans.size()-1);

  //   int element_idxf = dist_lf2(rng);
  //   int element_idxs = dist_ls2(rng);

  //   swap_array_and_update(num[fn][lf],element_idxf,num[sn][ls],element_idxs,original_pizza);

  // }

  rep(i,3){
    make_ans(num[i],2+i,false);
  }
  cout << pt << endl;
  return 0;
    

}

