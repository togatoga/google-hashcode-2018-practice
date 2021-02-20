#include <iostream>
#include <string>
using namespace std;
typedef long long ll;
//using nagai = long long;

const ll mod=1e9+7;
ll mu(ll a,ll b){
  return (ll)a*b%mod;
}
ll ad(ll a,ll b){
  if((a+=b)>=mod)a-=mod;
  return a;
}
ll pw(ll a,ll b,ll c=1LL){
  for(;b;b>>=1,a=mu(a,a))if(b&1)c=mu(c,a);
  return c;
}
ll dv(ll a,ll b){
  return mu(a,pw(b,mod-2));
}

int main() {
  int n = 5;
  int c[n + 1];

  c[0] = 1;
  for (int i = 1; i <= n; i++) {
    c[i] = mu(c[i - 1], mu(n - i + 1, dv(1,i)));
    cout << c[i] <<endl;
  }
  return 0;

}
