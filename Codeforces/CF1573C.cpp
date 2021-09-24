
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: CF1573C.cpp
	 date created: 2021-09-22 22:06:40
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
#define forll(i, start, end, step) for(ll i = start; i <= end; i += step)
#define fortype(type, i, start, end, step) for(type i = start; i != end; i += step)

//some useful algos
template <class T> T mceil(T a, T b){return (a % b == 0) ? a/b : a/b + 1;}
template <class T> T expo(T base , T exp , T mod){T res = 1;base = base % mod;while (exp > 0){if (exp & 1)res = (res*base) % mod;exp = exp>>1;base = (base*base) % mod;}return res;}
template <class T> ll maxpower(T a , T b){ll ans = 0;while(a > 0 && a % b == 0){ans++;a /= b;}return ans;}
template <class T> T extgcd(T a, T b , T &x , T &y) {x = 1, y = 0;T x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) { T q = a1 / b1; tie(x, x1) = make_tuple(x1, x - q * x1); tie(y, y1) = make_tuple(y1, y - q * y1); tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;}
template <class T> T modinv (T a , T m , T &x , T &y){T g = extgcd(a , m , x , y); if (g != 1) cerr << "Division by zero!"; else x = (x % m + m) % m; return x;}
template <class T> T signed_floor(T a , T b){if (a >= 0 && b >= 0) return a/b; else if (a < 0 & b < 0) return (-a)/(-b); else if (a < 0 & b >= 0){if (a % b == 0) return -((-a)/b); else return -((-a)/b) - 1;} else if (a >= 0 && b < 0){if(a % b == 0) return -(a/(-b)); else return -(a/(-b)) - 1;}}
template <class T> pair<T,T> log_base_2(T n){T temp = 1 , k = 0; while(temp <= n){temp <<= 1; k++;} temp >>= 1; k--; return {k , temp};}
//define global variables here
vector <pair<ll, ll> > blank;
vector <vector <pair<ll, ll> > > adj;
ll color[200000 + 1];
ll readings[200000 + 1];

ll dfs(ll v){
    ll cycle = 0;
    color[v] = 1;

    if (ssz(adj[v]) == 0){
        color[v] = 2;
        readings[v] = 0;
        return 0;
    }

    for(pair<ll, ll> p : adj[v]){
        ll u = p.first, w = p.second;
        if (color[u] == 0){
            cycle = cycle | dfs(u);
        }
        else if (color[u] == 1){
            cycle = 1;
        }
        readings[v] = max(readings[v], readings[u] + w);
    } 

    color[v] = 2;
    return cycle;
}


void solve(ll mcase){
    ll n;
    scanf("%lld", &n);

    adj.assign(n + 1, blank);
    memset(color, (ll)0, sizeof(ll)*(n + 1));
    memset(readings, (ll)0, sizeof(ll)*(n + 1));

    forll(i, 1, n, 1){
        ll ki;
        scanf("%lld", &ki);

        forll(j, 1, ki, 1){
            ll ai;
            scanf("%lld", &ai);

            if (ai > i){
                adj[i].push_back({ai, 1});
            }
            else{
                adj[i].push_back({ai, 0});
            }
        }
    }

    ll isCyclic = 0;
    forll(i, 1, n, 1){
        if (color[i] == 0){
            isCyclic = isCyclic | dfs(i); 
        }
    }

    if (isCyclic){
        printf("-1\n");
        return;
    }

    ll ans = -INF;
    forll(i, 1, n, 1){
        ans = max(readings[i], ans);
    }

    printf("%lld\n", ans + 1);
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
    
    ll t , mcase = 1; //testcases
    scanf("%lld\n", &t);
    while(t > 0){
    	solve(mcase); //write a separate solve function
    	t--;
    	mcase++;
    }
    
    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
