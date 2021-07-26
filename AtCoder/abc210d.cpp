
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: d.cpp
	 date created: 2021-07-17 18:11:21
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
ll a[1001][1001];
ll dp_right_down[1001][1001];
ll dp_left_down[1001][1001];

void solve(ll mcase){
    ll h, w, c;
    scanf("%lld %lld %lld", &h, &w, &c);

    for (ll i = 1; i <= h; i++){
        for (ll j = 1; j <= w; j++){
            scanf("%lld", &a[i][j]);
            dp_right_down[i][j] = INF;
            dp_left_down[i][j] = INF;
        }
    }
    //final answer
    ll ans = INF;

    //calculating dp_right_down
    for (ll i = h; i >= 1; i--){
        for (ll j = w; j >= 1; j--){
            if (j == w && i == h){
                dp_right_down[h][w] = a[h][w];
            }
            else{   
                if (i + 1 <= h){
                    dp_right_down[i][j] = min(dp_right_down[i][j], c + dp_right_down[i + 1][j]);
                }
                if (j + 1 <= w){
                    dp_right_down[i][j] = min(dp_right_down[i][j], c + dp_right_down[i][j + 1]);
                }
                //update answer
                ans = min(ans, a[i][j] + dp_right_down[i][j]);

                //the path that ends there
                dp_right_down[i][j] = min(dp_right_down[i][j], a[i][j]);
            }
        }
    }

    //calculating dp_left_down
    for (ll i = h; i >= 1; i--){
        for (ll j = 1; j <= w; j++){
            if (j == 1 && i == h){
                dp_left_down[h][1] = a[h][1];
            }
            else{   
                if (i + 1 <= h){
                    dp_left_down[i][j] = min(dp_left_down[i][j], c + dp_left_down[i + 1][j]);
                }
                if (j - 1 >= 1){
                    dp_left_down[i][j] = min(dp_left_down[i][j], c + dp_left_down[i][j - 1]);
                }
                //update answer
                ans = min(ans, a[i][j] + dp_left_down[i][j]);

                //the path that ends there
                dp_left_down[i][j] = min(dp_left_down[i][j], a[i][j]);
            }
        }
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
    /*
    ll t , mcase = 1; //testcases
    scanf("%lld\n", &t);
    while(t > 0){
    	solve(mcase); //write a separate solve function
    	t--;
    	mcase++;
    }
    */
    solve(1);
    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
