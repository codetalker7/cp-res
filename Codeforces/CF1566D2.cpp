
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: 5.cpp
	 date created: 2021-09-12 21:20:23
	 problem link: https://codeforces.com/contest/1566/problem/D2
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
ll sights[90000 + 1];
ll arrangement[90000 + 1];
ll pos[90000 + 1];
ll fenwick[90000 + 1];

ll n, m;

ll rep(ll a, ll b){
    if (b % a == 0){
        return b - a + 1;
    }
    else
        return b - (b % a) + 1;
}

bool comp(ll x, ll y){
    if (sights[x] == sights[y]){
        return x < y;
    }
    else{
        return sights[x] < sights[y];
    }
}
bool comp1(ll x, ll y){
    if (sights[x] == sights[y]){
        return x > y;
    }
    else{
        return sights[x] < sights[y];
    }
}

ll getsum(ll b){
    ll sum = 0;
    for (ll i = b; i > 0; i -= LSB(i))
        sum += fenwick[i];
    return sum;
}

ll query(ll a, ll b){
    if (b < a)
        return 0;
    return getsum(b) - (a == 1 ? 0 : getsum(a - 1));
}

void update(ll b, ll pos, ll v){
    for (ll i = pos; i <= b; i += LSB(i)){
        fenwick[i] += v;
    }
}

void solve(ll mcase){
    scanf("%lld %lld", &n, &m);

    for (ll i = 1; i <= n*m; i++){
        scanf("%lld", &sights[i]);
        arrangement[i] = i;
        pos[i] = i;
    }

    //permute arrangement
    sort(arrangement + 1, arrangement + n*m + 1, comp);

    //sort each layer independently
    for (ll i = 1; i <= n; i++){
        ll start_pos = m*(i - 1) + 1;
        sort(arrangement + start_pos, arrangement + start_pos + m, comp1);
    }



    //set pos
    for (ll i = 1; i <= n*m; i++){
        pos[arrangement[i]] = i;
    }

    //initialise fenwick tree
    for (ll i = 1; i <= n*m; i++)
        fenwick[i] = 0;

    //do the same thing
    ll ans = 0;

    for (ll i = 1; i <= n*m; i++){
        //get the left endpoint to which i belongs
        ll l;
        if (pos[i] % m == 0){
            l = pos[i] - m + 1;
        }
        else{
            l = pos[i] - (pos[i] % m) + 1;
        }

        //get the sum in range [l,pos[i])
        ans += query(l, pos[i] - 1);

        //point update pos[i]
        update(n*m, pos[i], 1);
    }
    printf("%lld\n", ans);
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
