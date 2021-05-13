
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: VPATH
	 date created: 2021-05-11 21:29:38
	 problem link: https://www.codechef.com/MAY21C/problems/VPATH
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
vector <vll> adj;
vll color;
vll parent;
vll D;
vll A;
vll blank;
vll leaves;

void find_parent(ll s){
    queue <ll> mq;
    color[s] = 1;
    parent[s] = -1;
    mq.push(s);

    //finding parents and leaves
    leaves.clear();
    while(!mq.empty()){
        ll top = mq.front();
        mq.pop();

        ll flag = 1;
        for (auto u : adj[top]){
            if (color[u] == 0){
                flag = 0;
                color[u] = 1;
                parent[u] = top;
                mq.push(u);
            }
        }

        //checking if the current vertex is a leaf
        if (flag == 1)
            D[top] = 1;
        //to process later
        leaves.push_back(top);
    }
}

void final_ans(ll s , ll N){
    ll ans = 0;

    queue <ll> mq;
    color[s] = 4;
    A[s] = D[s];
    ans = (ans + A[s]) % MOD;
    mq.push(s);

    while(!mq.empty()){
        ll top = mq.front();
        mq.pop();

        for (auto u : adj[top]){
            if (color[u] <= 3){
                color[u] = 4;
                A[u] = (2 * A[top] - 3 * D[u] + MOD) % MOD;
                ans = (ans + A[u]) % MOD;
                mq.push(u);
            }
        }
    }
    ans = (ans + 3 * N) % MOD;

    //final answer
    cout << (ans * 250000002) % MOD << "\n";
}

void solve(ll mcase){
    ll N;
    cin >> N;

    adj.assign(N + 1 , blank);
    color.assign(N + 1 , 0);
    parent.assign(N + 1 , 0);
    D.assign(N + 1 , 0);
    A.assign(N + 1 , 0);
    
    for (ll i = 1; i <= N - 1; i++){
        ll u , v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    //finding the parents using bfs
    find_parent(1);

    //computing D values bottom up
    while (!leaves.empty()){
        ll top = leaves.back();
        leaves.pop_back();

        if (parent[top] != -1){
            if (color[parent[top]] == 1){
                D[parent[top]] = (D[parent[top]] + 1 + 2 * D[top]) % MOD;
                color[parent[top]] = 2;
            }
            //color[parent[top]] must be 2
            else
                D[parent[top]] = (D[parent[top]] + 2 * D[top]) % MOD;
        }
    }

    //computing the final answer with another bfs
    final_ans(1 , N);
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
    
    ll t , mcase = 1; //testcases
    cin >> t;
    while(t > 0){
    	solve(mcase); //write a separate solve function
    	t--;
    	mcase++;
    }
    
    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
