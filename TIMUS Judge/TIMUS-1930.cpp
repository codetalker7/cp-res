
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: TIMUS-1930
	 date created: 2021-05-14 20:00:32
	 problem link: https://acm.timus.ru/problem.aspx?space=1
*/
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<stack>
#include<unordered_set>
#include<cmath>
#include<numeric>
#include<iterator>
#include<set>
#include<unordered_map>
#include<map>
#include<queue>
#include<cstring>
#include<stdio.h>
#include<fstream>
#include<iomanip>
#include<functional>
#include<bitset>
#include<chrono>
#include<climits>
#include<assert.h>
using namespace std;

//type declarations
using ll = long long int;
using ull = unsigned long long int;
using vint = vector<int>;
using vll = vector<ll>;
using vch = vector<char>;
using vs = vector<string>;
using sll = set<ll>;
using msll = multiset<ll>;
using ldb = long double;

//constants
const ll MOD = 1000000007;
const ll INF = 1e18;
const int INFINT = 1e9 + 5;
const ldb PI = 3.14159265359;

//some useful algos
template <class T> T mceil(T a, T b){return (a % b == 0) ? a/b : a/b + 1;}
template <class T> T expo(T base , T exp , T mod){T res = 1;base = base % mod;while (exp > 0){if (exp & 1)res = (res*base) % mod;exp = exp>>1;base = (base*base) % mod;}return res;}
template <class T> ll maxpower(T a , T b){ll ans = 0;while(a > 0 && a % b == 0){ans++;a /= b;}return ans;}
template <class T> T extgcd(T a, T b , T &x , T &y) {x = 1, y = 0;T x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) { T q = a1 / b1; tie(x, x1) = make_tuple(x1, x - q * x1); tie(y, y1) = make_tuple(y1, y - q * y1); tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;}
template <class T> T modinv (T a , T m , T &x , T &y){T g = extgcd(a , m , x , y); if (g != 1) cerr << "Division by zero!"; else x = (x % m + m) % m; return x;}
template <class T> T signed_floor(T a , T b){if (a >= 0 && b >= 0) return a/b; else if (a < 0 & b < 0) return (-a)/(-b); else if (a < 0 & b >= 0){if (a % b == 0) return -((-a)/b); else return -((-a)/b) - 1;} else if (a >= 0 && b < 0){if(a % b == 0) return -(a/(-b)); else return -(a/(-b)) - 1;}}
template <class T> pair<T,T> log_base_2(T n){T temp = 1 , k = 0; while(temp <= n){temp <<= 1; k++;} temp >>= 1; k--; return {k , temp};}
//define global variables here

vector <vector <pair <ll , ll> > > adj;
vector <pair <ll , ll> > blank;
vll d1, d2;

void solve(ll mcase){

}

void dijkstra(vll &d , ll source){
	d[source] = 0;
	set<pair <ll , ll> > q;
	q.insert({0 , source});

	while(!q.empty()){
		ll v = (*q.begin()).second;
		q.erase(q.begin());

		for (auto edge : adj[v]){
			ll to = edge.first;
			ll len = edge.second;

			if (d[v] + len < d[to]){
				q.erase({d[to] , to});
				d[to] = d[v] + len;
				q.insert({d[to] , to});
			}
		}
	}
}

//main function
int main(){
    //faster io
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

/*
    if there is an online judge, we use the
    standard io streams. Otherwise, we use custom
    io files.
*/
#ifndef ONLINE_JUDGE
    //works in codechef and codeforces
    FILE* inp = freopen("input.txt", "r" , stdin);
    FILE* err = freopen("error.txt", "w" , stderr);
    FILE* out = freopen("output.txt", "w" , stdout);
#endif

    //for testcases, use the below format
    /*
    ll t , mcase = 1; //testcases
    cin >> t;
    while(t > 0){
    	solve(mcase); //write a separate solve function
    	t--;
    	mcase++;
    }
    */
    ll n , m;
    cin >> n >> m;

   	//making the adjacency list
    adj.assign(2*n + 1 , blank);
  	d1.assign(2*n + 1 , INF);
  	d2.assign(2*n + 1 , INF);

    for (ll i = 1; i <= m; i++){
    	ll u , v;
    	cin >> u >> v;

    	adj[2*u - 1].push_back({2*v - 1 , 0});
    	adj[2*u].push_back({2*v - 1 , 1});

    	adj[2*v].push_back({2*u , 0});
    	adj[2*v - 1].push_back({2*u , 1});
    }

    ll S , T;
    cin >> S >> T;

    dijkstra(d1 , 2*S - 1);
    dijkstra(d2 , 2*S);

    ll ans = min(d1[2*T] , d1[2*T - 1]);
    ans = min(ans , d2[2*T]);
    ans = min(ans , d2[2*T - 1]);
    cout << ans;

    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
