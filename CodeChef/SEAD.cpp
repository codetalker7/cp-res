
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: SEAD
	 date created: 2021-05-04 16:03:48
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

void solve(ll mcase){

}

void build(vll diff , vll &segTree){
    ll n = diff.size();
    for (ll i = 0; i < n; i++){
        segTree[i + n] = diff[i];
    }
    for (ll i = n - 1; i > 0; i--){
        segTree[i] = max(segTree[i << 1] , segTree[i << 1 | 1]);
    }
}

//max query in the range [l , r)
ll query(vll segTree , ll l , ll r){
    ll res = -INF, n = segTree.size() / 2;
    l += n; r += n;

    while (l < r){
        if (l & 1){
            res = max(res , segTree[l]); l += 1; l >>= 1;
        }
        else 
            l >>= 1;
        if (r & 1){
            res = max(res , segTree[r - 1]); r >>= 1;
        }
        else 
            r >>= 1;
    }
    return res;
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
    /*
    ll t , mcase = 1; //testcases
    cin >> t;
    while(t > 0){
    	solve(mcase); //write a separate solve function
    	t--;
    	mcase++;
    }
    */
    //taking the input
    ll n;
    cin >> n;

    vll marr(n);
    for (ll i = 0; i < n; i++)
        cin >> marr[i];

    ll m; 
    cin >> m;

    //making the difference array
    vll diff(n - 1);
    for (ll i = 0; i < n - 1; i++){
        diff[i] = marr[i + 1] - marr[i];
    }

    //building the segment tree for diff
    vll segTree(2 * diff.size());
    build(diff , segTree);

    //handling the queries
    for (ll x = 0; x < m; x++){
        ll t , d;
        cin >> t >> d;

        /*
            Note that for such a t, there is a unique k such that a_k <= t and a_{k + 1} > t. 
            Using binary search, find this k. Let D[0,...,n - 2] be the difference array.
            Again using binary search, find the smallest index i<= k such that the range
            minimum of D in the range [i , k - 1] is atmost d.
        */

        //finding k using binary search
        ll k;
        if (marr[n - 1] <= t){
            k = n - 1;
        }
        else {
            ll lo = 0 , hi = n - 1;
            ll flag = 0;
            while (lo <= hi){
                ll mid = lo + (hi - lo + 1)/2;
                if (marr[mid] <= t && marr[mid + 1] > t){
                    k = mid;
                    break;
                }
                else if (marr[mid] > t){
                    hi = mid - 1;
                }
                else{
                    lo = mid;
                }
            }
        }

        //finding i using binary search
        ll lo = 0 , hi = k - 1 , mid;
        ll flag = 0;
        while (lo <= hi){
            mid = lo + (hi - lo)/2;
            ll y = query(segTree , mid , k);
            if (y <= d){
                if (lo == mid){
                    flag = 1;
                    break;
                }
                else 
                    hi = mid;
            }
            else{
                lo = mid + 1;
            }
        }
        //if query(segTree , mid , k) <= d
        if (flag == 1)
            cout << mid + 1 << "\n";
        else 
            cout << k + 1 << "\n";
        
    }
    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
