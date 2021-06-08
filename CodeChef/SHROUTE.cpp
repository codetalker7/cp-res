
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: SHROUTE
	 date created: 2021-06-06 01:05:21
	 problem link: https://www.codechef.com/JUNE21B/problems/SHROUTE
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
ll A[100000 + 1];
ll B[100000 + 1];
ll L[100000 + 1];
ll R[100000 + 1];

void solve(ll mcase){
    ll N, M;
    cin >> N >> M;

    vll left, right;

    //taking the input
    for (ll i = 1; i <= N; i++){
        cin >> A[i]; 
        if (A[i] == 1)
            right.push_back(i);
        else if (A[i] == 2){
            left.push_back(i);
        }
    }
    for (ll i = 1; i <= M; i++){
        cin >> B[i];
    }

    //setting the L and R arrays using binary search
    for (ll i = 1; i <= N; i++){
        if (A[i] != 0){
            L[i] = i;
            R[i] = i;
            continue;
        }
        //else there is no train emerging from i
        //setting L[i] first
        ll lo, hi, mid;
        if (ssz(right) == 0 || right[0] > i)
            L[i] = INF;
        else{
            lo = 0; hi = ssz(right) - 1;
            while(lo <= hi){
                mid = lo + (hi - lo + 1)/2;
                if (right[mid] < i){
                    if (lo == mid)
                        break;
                    else
                        lo = mid;
                }
                else
                    hi = mid - 1;
            }
            L[i] = right[mid];   
        } 

        //setting R[i]
        if (ssz(left) == 0 || left[ssz(left) - 1] < i)
            R[i] = INF;
        else{
            lo = 0; hi = ssz(left) - 1;
            while(lo <= hi){
                mid = lo + (hi - lo)/2;
                if (left[mid] > i){
                    if (lo == mid)
                        break;
                    else
                        hi = mid;
                }
                else
                    lo = mid + 1;
            }
            R[i] = left[mid];   
        }
    }   
    for (ll i = 1; i <= M; i++){
        if (A[B[i]] != 0 || B[i] == 1){
            cout << 0 << " ";
            continue;
        }
        ll ans = min(abs(B[i] - L[B[i]]), abs(B[i] - R[B[i]]));
        if (L[B[i]] == INF && R[B[i]] == INF)
            cout << -1 << " ";
        else
            cout << ans << " ";
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
    cin >> t;
    while(t > 0){
    	solve(mcase); //write a separate solve function
    	t--;
    	mcase++;
    }
    
    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
