/*
    template-by: a_new_beginning  
    editor: sublime text 3
    uva-796: critical links
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

//define global variables here
vector <vll> adj;
vll blank;

//dfs variables
vector <ll> color;
vector <ll> parent;
vector <ll> low;
vector <ll> discovery;
vector <ll> finish;
queue <ll> leaves;

//storing the bridges
vector <pair <ll , ll>> bridges;

void dfs(ll source , ll &time){
    color[source] = 1;
    discovery[source] = time;
    time++;

    //initialize low to discovery[source]
    low[source] = discovery[source];

    ll flag = 0;
    for (auto u : adj[source]){
        if (color[u] == 0){
            flag = 1;
            parent[u] = source;
            dfs(u , time);
        }
    }
    
    if(!flag){
        leaves.push(source);
    }
    color[source] = 2;
    finish[source] = time;
    time++;
}

int solve(){
    ll N = -1; scanf("%lld" , &N);
    if (N < 0)
        return 0;

    //cleanup
    adj.clear();
    color.clear();
    parent.clear();
    low.clear();
    discovery.clear();
    finish.clear();
    leaves = queue<ll>();
    bridges.clear();

    //initializing
    for (ll i = 1; i <= N; i++){
        adj.push_back(blank);
        color.push_back(0);
        parent.push_back(-1);
        low.push_back(-1);
        discovery.push_back(-1);
        finish.push_back(-1);
    }

    for (ll i = 1; i <= N; i++){
        ll K , M;
        scanf("%lld (%lld)" , &K , &M);

        for (ll j = 1; j <= M; j++){
            ll x;
            scanf("%lld" , &x);
            adj[K].push_back(x);
        }
    }

    ll time = 0;
    //doing the dfs
    for (ll i = 0; i < N; i++){
        if (color[i] == 0){
            dfs(i , time);
        }
    }
    
    //computing low values
    while(!leaves.empty()){
        ll u = leaves.front();
        leaves.pop();
        if (parent[u] != -1)
            leaves.push(parent[u]);
        for (auto v : adj[u]){
            //checking for back edge
            if (discovery[v] < discovery[u] && finish[v] > finish[u] && v != parent[u])
                low[u] = min(low[u] , discovery[v]);
        }
        if (parent[u] != -1)
            low[parent[u]] = min(low[parent[u]] , low[u]);
    }
    //getting the bridges
    for (ll i = 0; i < N; i++){
        if (parent[i] != -1){
            if(low[i] > discovery[parent[i]]){
                if (parent[i] < i)
                    bridges.push_back(pair<ll , ll>(parent[i] , i));
                else 
                    bridges.push_back(pair<ll , ll>(i , parent[i]));
            }
        }
    }
    sort(bridges.begin() , bridges.end());

    //printing the bridges
    printf("%lld critical links\n", ll(bridges.size()));
    for (ll i = 0; i < bridges.size(); i++){
        printf("%lld - %lld\n", bridges[i].first , bridges[i].second);
    }
    printf("\n");

    return 1;
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
    
    ll flag = 1;
    while(flag){
    	flag = solve(); //write a separate solve function
    }
    
    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}