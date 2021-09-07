
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: 4.cpp
	 date created: 2021-09-01 23:00:58
	 problem link: 
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
#include<random>
using namespace std;

//debugging functions
//var_name is used to give the variable name
void debug(char x){cerr << x;}
void debug(int x){cerr << x;}
void debug(unsigned int x){cerr << x;}
void debug(long long x){cerr << x;}
void debug(unsigned long long x){cerr << x;}
void debug(long double x){cerr << x;}
void debug(double x){cerr << x;}
void debug(string x){cerr << x;}
void debug(float x){cerr << x;}

template <class T, class V> void debug(pair <T, V> x){cerr << "(" << x.first << "," << x.second << ")";}
template <class T> void debug(vector <T> v){cerr<<"[ ";for(T i: v){debug(i);cerr<<" ";}cerr << "]";}
template <class T> void debug(set <T> v){cerr<<"{ ";for(T i: v){debug(i);cerr<<" ";}cerr << "}";}
template <class T> void debug(multiset <T> v){cerr<<"{ ";for(T i: v){debug(i);cerr<<" ";}cerr << "}";}
template <class T, class V> void debug(map <T, V> v){cerr<<"[ ";for(auto i: v){debug(i);cerr<<" ";}cerr << "]";}
//debug with a new line at the end
#define debugln(x) debug(x); cerr << "\n"

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

//Logical Operators
#define AND &&
#define OR ||
#define NOT(x) !x

//Bit Manipulation
#define LSB(x) x & (-x) //value of least significant bit

//macros
/*
	ssz refers to the signed size of an STL structure, because .size() function
	returns an unsigned integer
*/
#define ssz(x) (int)x.size()

//some useful algos
template <class T> T mceil(T a, T b){return (a % b == 0) ? a/b : a/b + 1;}
template <class T> T expo(T base , T exp , T mod){T res = 1;base = base % mod;while (exp > 0){if (exp & 1)res = (res*base) % mod;exp = exp>>1;base = (base*base) % mod;}return res;}
template <class T> ll maxpower(T a , T b){ll ans = 0;while(a > 0 && a % b == 0){ans++;a /= b;}return ans;}
template <class T> T extgcd(T a, T b , T &x , T &y) {x = 1, y = 0;T x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) { T q = a1 / b1; tie(x, x1) = make_tuple(x1, x - q * x1); tie(y, y1) = make_tuple(y1, y - q * y1); tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;}
template <class T> T modinv (T a , T m , T &x , T &y){T g = extgcd(a , m , x , y); if (g != 1) cerr << "Division by zero!"; else x = (x % m + m) % m; return x;}
template <class T> T signed_floor(T a , T b){if (a >= 0 && b >= 0) return a/b; else if (a < 0 & b < 0) return (-a)/(-b); else if (a < 0 & b >= 0){if (a % b == 0) return -((-a)/b); else return -((-a)/b) - 1;} else if (a >= 0 && b < 0){if(a % b == 0) return -(a/(-b)); else return -(a/(-b)) - 1;}}
template <class T> pair<T,T> log_base_2(T n){T temp = 1 , k = 0; while(temp <= n){temp <<= 1; k++;} temp >>= 1; k--; return {k , temp};}
//define global variables here
vll blank;
vector <vll> adj1;
vector <vll> adj2;
vll color1;
vll color2;

//dsu 
vll rank1, rank2;
vll root1, root2;

ll findRoot(ll x, vll &root){
    root[x] = (x == root[x]) ? x : findRoot(root[x], root);
    return root[x];
}

void makeUnion(ll x, ll y, vll &rank, vll &root){
    ll a = findRoot(x, root), b = findRoot(y, root);
    if (a != b){
        if (rank[a] >= rank[b]){
            root[a] = b; rank[b]++;
        }
        else{
            root[b] = a; rank[a]++;
        }
    }
}

void bfs(ll n, ll s, vll &color, vector <vll> &adj, vll &root, vll &rank){
    queue <ll> q;

    q.push(s);  
    color[s] = 1;

    while (!q.empty()){
        ll v = q.front();
        q.pop();

        for (ll u : adj[v]) {
            if (!color[u]){
                color[u] = 1;
                makeUnion(s, u, rank, root);
                q.push(u);
            }
        }
    }

}

void solve(ll mcase){
    ll n, m1, m2;
    scanf("%lld %lld %lld", &n, &m1, &m2);

    //adj lists
    adj1.assign(n + 1, blank);
    adj2.assign(n + 1, blank);

    //colors
    color1.assign(n + 1, 0);
    color2.assign(n + 1, 0);

    //dsu ranks and roots
    rank1.assign(n + 1, 0);
    rank2.assign(n + 1, 0);

    root1.assign(n + 1, 0);
    root2.assign(n + 1, 0);

    //setting the roots
    for (ll i = 1; i <= n; i++){
        root1[i] = i;
        root2[i] = i;
    }

    for (ll i = 1; i <= m1; i++){
        ll u, v;
        scanf("%lld %lld", &u, &v);
        adj1[u].push_back(v);
        adj1[v].push_back(u);
    }

    for (ll i = 1; i <= m2; i++){
        ll u, v;
        scanf("%lld %lld", &u, &v);
        adj2[u].push_back(v);
        adj2[v].push_back(u);
    }

    //set the components for the first graph
    for (ll i = 1; i <= n; i++){
        if (color1[i] == 0){
            bfs(n, i, color1, adj1, root1, rank1);
        }
    }

    //set the components for the second graph
    for (ll i = 1; i <= n; i++){
        if (color2[i] == 0){
            bfs(n, i, color2, adj2, root2, rank2);
        }
    }
        
    //go over each pair
    vector <pair<ll, ll> > edges;
    for (ll i= 1; i <= n; i++){
        for (ll j = i + 1; j <= n; j++){
            ll r1 = findRoot(i, root1), r2 = findRoot(i, root2);
            ll R1 = findRoot(j, root1), R2 = findRoot(j, root2);
            if (r1 != R1 AND r2 != R2){
                makeUnion(i, j, rank1, root1);
                makeUnion(i, j, rank2, root2);
                edges.push_back({i, j});
            }
        }
    }
    printf("%lld\n", (ll)ssz(edges));
    for (ll i = 0; i < ssz(edges); i++)
        printf("%lld %lld\n", edges[i].first, edges[i].second);
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
    /*
        Uncomment the next line to use the
        Mersenne Twister Random Number 
        Generator, with the current system 
        time as the seed. 
        The first line is for 32-bit
        Second line is for 64-bit
    */
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    //mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());


    //for testcases, use the below format
    
    /*ll t , mcase = 1; //testcases
    scanf("%lld\n", &t);
    while(t > 0){
    	solve(mcase); //write a separate solve function
    	t--;
    	mcase++;
    }*/
    solve(1);
    
    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
