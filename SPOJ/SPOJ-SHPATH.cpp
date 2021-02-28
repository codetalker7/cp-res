/*
    template-by: codetalker7
    editor: sublime text 3
    SPOJ: SHPATH
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
using pllii = pair <ll , ll>;

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

//define global variables here

map <string , ll> names_indexes;
vector <vector <pair <ll , ll> > > adj;
vector <pair <ll , ll> > blank;

ll dijkstra(ll s , ll t){
    ll n = adj.size();
    vll d; d.assign(n + 1 , INF);

    d[s] = 0;
    priority_queue<pllii , vector <pllii> , greater<pllii>> q;
    q.push({0 , s});

    while(!q.empty()){
        ll v = q.top().second;
        ll d_v = q.top().first;
        q.pop();

        if(d_v != d[v])
            continue;

        for (auto edge : adj[v]){
            ll to = edge.first;
            ll len = edge.second;

            if(d[v] + len < d[to]){
                d[to] = d[v] + len;
                q.push({d[to] , to});
            }
        }
    }
    return d[t];
}

void solve(){
    ll n; cin >> n; //number of cities
    names_indexes.clear();
    adj.assign(n + 1 , blank);

    //taking the input
    for (ll i = 1; i <= n; i++){
        string temp; cin >> temp; //name of the city
        names_indexes.insert(pair <string , ll>(temp , i));
        ll neigh; cin >> neigh;
        for (ll j = 0; j < neigh; j++){
            ll nr , cost;
            cin >> nr >> cost;
            adj[i].push_back(pair<ll , ll>(nr , cost));
        }
    }
    ll r; cin >> r; //number of paths to find
    while (r > 0){
        string NAME1 , NAME2;
        cin >> NAME1 >> NAME2;

        ll p , q;
        p = names_indexes[NAME1]; q = names_indexes[NAME2];

        cout << dijkstra(p , q) << "\n";
        //decrement r
        r--;
    }
    cout << "\n";
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

    ll t; //testcases
    cin >> t;
    while(t > 0){
    	solve(); //write a separate solve function
    	t--;
    }

    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
