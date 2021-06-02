
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: abc203_d
	 date created: 2021-05-30 18:42:28
	 problem link: https://atcoder.jp/contests/abc203/tasks/abc203_d
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
ll pref[801][801];
ll A[801][801];
ll B[801][801];

bool check(ll X, ll N, ll K){
    for (ll i = 1; i <= N; i++){
        for (ll j = 1; j <= N; j++){
            //setting the values of B
            if (A[i][j] <= X)
                B[i][j] = 1;
            else 
                B[i][j] = 0;

            //setting the values of pref
            if (i == 1 && j == 1)
                pref[1][1] = B[1][1];
            else{
                if (i == 1)
                    pref[i][j] = pref[i][j - 1] + B[i][j];
                else if (j == 1){
                    pref[i][j] = pref[i - 1][j] + B[i][j];
                }
                else{
                    pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + B[i][j];
                }
            }
        }
    }
    //checking if the sum of any K*K submatrix is atleast K^2 + 1
    for (ll i = 1; i <= N - K + 1; i++){
        for (ll j = 1; j <= N - K + 1; j++){
            //need the sum from (i , j) to (i + K - 1 , j + K - 1)
            ll sum;
            if (i == 1 && j == 1){
                sum = pref[i + K - 1][j + K - 1];
            }
            else if (i == 1){
                sum = pref[i + K - 1][j + K - 1] - pref[i + K - 1][j - 1];
            }
            else if (j == 1){
                sum = pref[i + K - 1][j + K - 1] - pref[i - 1][j + K - 1];
            }
            else{
                sum = pref[i + K - 1][j + K - 1] - pref[i - 1][j + K - 1] - pref[i + K - 1][j - 1] + pref[i - 1][j - 1];
            }
            if (K % 2 == 0){
                if (sum >= (K*K)/2)
                    return 1;
            }
            else{
                if (sum >= (K*K)/2 + 1)
                    return 1;
            }
        }
    }
    return 0;
}

void solve(){
    ll N, K;
    cin >> N >> K;

    ll MAXN = -INF;

    for(ll i = 1; i <= N; i++){
        for (ll j = 1; j <= N; j++){
            cin >> A[i][j];
            MAXN = max(MAXN , A[i][j]);
        }
    }
    ll lo = 0, hi = MAXN , mid;
    while(lo <= hi){
        mid = lo + (hi - lo)/2;
        if (check(mid, N, K)){
            if(lo == mid)
                break;
            else
                hi = mid;
        }
        else
            lo = mid + 1;
    }
    cout << mid << "\n";
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
    cin >> t;
    while(t > 0){
    	solve(mcase); //write a separate solve function
    	t--;
    	mcase++;
    }
    */
    solve();
    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
