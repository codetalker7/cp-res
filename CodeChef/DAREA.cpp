
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: DAREA
	 date created: 2021-06-07 23:57:29
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

struct Triple{
    ll coord, mmin, mmax;
};
  
ll calculateMin(vector <Triple> bar){
    ll total = ssz(bar);
    if (total == 1 || total == 2){
        return 0;
    }

    vll area_right(total), area_left(total);

    //calculating area_right
    ll curr_min, curr_max;
    for (ll i = total - 1; i >= 0; i--){
        if (i == total - 1){
            curr_min = bar[i].mmin;
            curr_max = bar[i].mmax;
            area_right[i] = INF;
        }
        else{
            area_right[i] = (curr_max - curr_min) * (bar[total - 1].coord - bar[i + 1].coord);
            curr_min = min(curr_min, bar[i].mmin);
            curr_max = max(curr_max, bar[i].mmax);
        }
    }

    //calculating area_left
    for (ll i = 0; i < total; i++){
        if (i == 0){
            curr_min = bar[i].mmin;
            curr_max = bar[i].mmax;
            area_left[i] = INF;
        }
        else{
            area_left[i] = (curr_max - curr_min) * (bar[i - 1].coord - bar[0].coord);
            curr_min = min(curr_min, bar[i].mmin);
            curr_max = max(curr_max, bar[i].mmax);
        }
    }

    ll ans = INF;
    for (ll i = 0; i < total; i++){
        if (i == 0){
            ans = min(ans, area_right[i]);
        }
        else if (i == total - 1){
            ans = min(ans, area_left[i]);
        }
        else{
            ans = min(ans, area_left[i] + area_right[i - 1]);
            ans = min(ans, area_left[i + 1] + area_right[i]);   
        }
    }
    return ans;
}

void solve(ll mcase){
    ll N;
    cin >> N;

    vector <pair<ll, ll> > points_v;
    vector <pair<ll, ll> > points_h;

    for (ll i = 1; i <= N; i++){
        ll x, y;
        cin >> x >> y;

        points_h.push_back({y, x});
        points_v.push_back({x, y});
    }
    sort(points_v.begin(), points_v.end());
    sort(points_h.begin(), points_h.end());

    vector <Triple> barv;
    vector <Triple> barh;

    for(ll i = 0; i < N; i++){
        //setting barv
        if (ssz(barv) == 0 || points_v[i].first > barv[ssz(barv) - 1].coord){
            Triple p; 
            p.coord = points_v[i].first;
            p.mmax = points_v[i].second;
            p.mmin = points_v[i].second;
            barv.push_back(p);
        }
        else{
            barv[ssz(barv) - 1].mmax = max(barv[ssz(barv) - 1].mmax, points_v[i].second);
            barv[ssz(barv) - 1].mmin = min(barv[ssz(barv) - 1].mmin, points_v[i].second);
        }

        //setting barh
        if (ssz(barh) == 0 || points_h[i].first > barh[ssz(barh) - 1].coord){
            Triple p; 
            p.coord = points_h[i].first;
            p.mmax = points_h[i].second;
            p.mmin = points_h[i].second;
            barh.push_back(p);
        }
        else{
            barh[ssz(barh) - 1].mmax = max(barh[ssz(barh) - 1].mmax, points_h[i].second);
            barh[ssz(barh) - 1].mmin = min(barh[ssz(barh) - 1].mmin, points_h[i].second);
        }
    }
    cout << min(calculateMin(barv), calculateMin(barh)) << "\n"; 
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
