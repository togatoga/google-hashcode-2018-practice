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


  
  return 0;
    

}
