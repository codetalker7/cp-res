
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: RICHSTR
	 date created: 2021-05-04 14:31:41
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
vll segTree;

void build(vll marr , ll n){
	for (ll i = 0; i < n; i++){
		segTree[i + n] = marr[i];
	}
	for (ll i = n - 1; i > 0; i--){
		segTree[i] = max(segTree[i << 1] , segTree[i << 1 | 1]);
	}
}

//range max in the range [l , r)
ll query(ll n , ll l , ll r){
	ll res = 0;
	l += n; r += n;
	while (l < r){
		//if l is a right child
		if (l & 1){
			res = max(res , segTree[l]); l += 1; l >>= 1;
		}
		else 
			l >>= 1;
		//if r is a right child
		if (r & 1){
			res = max(res , segTree[r - 1]); r >>= 1;
		}
		else 
			r >>= 1;
	}
	return res;
}

void solve(ll mcase){
	//taking the input
	ll N , Q;
	cin >> N >> Q;

	string str;
	cin >> str;

	//precomputing the new array
	vll marr(max((ll)0 , N - 2));
	for (ll i = 0; i < max((ll)0 , N - 2); i++){
		//checking for xxy
		if (str[i] == str[i + 1])
			marr[i] = 1;
		//checking for xyx
		else if (str[i] == str[i + 2])
			marr[i] = 1;
		//checking for yxx
		else if (str[i + 1] == str[i + 2])
			marr[i] = 1;
		else 
			marr[i] = 0;
	}
	//building the segment tree
	segTree.assign(2 * marr.size() , 0);
	build(marr , marr.size());

	//handling the queries
	for (ll counter = 0; counter < Q; counter++){
		ll L , R;
		cin >> L >> R;
		L--; R--;

		/*
			The answer for a query is YES if and only if the substring
			contains a subsubstring of the form xxy, xyx or yxx. So, the idea is to
			index all the three length substrings of str, assign them a value
			(either 0 or 1), and then check whether atleast one of the substrings belonging to the 
			interval L , R have value 1. This is equivalent to checking a range max query
		*/
		if (R - L + 1 < 3)
			cout << "NO\n";
		//if not, L <= R - 2 will always be true. 
		else if (query(marr.size() , L , R - 1) == 1)
			cout << "YES\n";
		else 
			cout << "NO\n";
	}
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
